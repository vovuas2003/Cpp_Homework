#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "player.hpp"
#include "player_states.hpp"



Player::Player(sf::Vector2f position) : mPosition{position}
{
    if (!mTexture.loadFromFile("./hero.png"))
    {
        std::cerr << "Can't load image ./hero.png for Player class" << std::endl;
        std::exit(1);
    }

    setState(new Idle(this));

    mSprite.setTexture(mTexture);
    mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
    mSprite.setPosition(mPosition);

    
    mScaleFactor = 4;
    mSprite.setScale(mScaleFactor, mScaleFactor);
}

void Player::setState(PlayerState* pNewState)
{
    delete mpState;
    mpState = pNewState;
}


sf::Vector2f Player::getCenter() const
{
    return mPosition;
}


void Player::applyVelocity(sf::Vector2f velocity)
{
    mVelocity += velocity;
}

void Player::update(float dt)
{
    mpState->update(this, dt);
    mPosition += mVelocity * dt;

    mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
    mSprite.setPosition(mPosition);
    mpState->updateSprite(mSprite, mIsFacedRight, mScaleFactor);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(mSprite);
    //if (true) // For debuging
    if (false)
    {
        sf::RectangleShape shape {{mCollisionRect.width, mCollisionRect.height}};
        shape.setPosition(mPosition.x + mCollisionRect.left, mPosition.y + mCollisionRect.top);
        shape.setFillColor(sf::Color(150, 50, 50, 90));
        window.draw(shape);

        sf::CircleShape center {6};
        center.setFillColor(sf::Color::Red);
        center.setOrigin(center.getRadius(), center.getRadius());
        center.setPosition(mPosition);
        window.draw(center);
    }
}


void Player::handleEvents(const sf::Event& event) 
{
    mpState->handleEvents(this, event);
}

bool Player::handleCollision(const my_block& rectt)
{
    sf::FloatRect playerRect = {mPosition.x + mCollisionRect.left, mPosition.y + mCollisionRect.top, mCollisionRect.width, mCollisionRect.height};
    auto rect = rectt.mblock;
    float overlapx1 = playerRect.left + playerRect.width - rect.left;
    float overlapx2 = rect.left + rect.width - playerRect.left;
    float overlapy1 = playerRect.top + playerRect.height - rect.top;
    float overlapy2 = rect.top + rect.height - playerRect.top;

    if (overlapx1 < 0 || overlapx2 < 0 || overlapy1 < 0 || overlapy2 < 0)
        return false;


    int minOverlapDirection = 0;
    float minOvelap = overlapx1;
    if (overlapx2 < minOvelap) {minOverlapDirection = 1; minOvelap = overlapx2;}
    if (overlapy1 < minOvelap) {minOverlapDirection = 2; minOvelap = overlapy1;}
    if (overlapy2 < minOvelap) {minOverlapDirection = 3;}

    switch (minOverlapDirection)
    {
        case 0:
            mPosition.x -= overlapx1 - 1;
            if (mVelocity.y > 0 && playerRect.top < rect.top + Hooked::kMaxHookOffset && playerRect.top > rect.top - Hooked::kMaxHookOffset)
            {
                mpState->hook(this);
            }
            break;
        case 1:
            mPosition.x += overlapx2 - 1;
            if (mVelocity.y > 0 && playerRect.top < rect.top + Hooked::kMaxHookOffset && playerRect.top > rect.top - Hooked::kMaxHookOffset)
            {
                mpState->hook(this);
            }
            break;
        case 2:
            mPosition.y -= overlapy1 - 1;
            mVelocity.y = 0;
            mVelocity.y = 0;
            mpState->hitGround(this);
            break;
        case 3:
            mPosition.y += overlapy2 - 1;
            if (mVelocity.y < 0)
            {
                mVelocity.y = 0;
                mVelocity.y = 0;
            }
            break;
    }
    return true;
}

bool Player::my_handleCollision(const my_block& rectt)
{
    sf::FloatRect playerRect = {mPosition.x + mCollisionRect.left, mPosition.y + mCollisionRect.top, mCollisionRect.width, mCollisionRect.height};
    auto rect = rectt.mblock;
    float overlapx1 = playerRect.left + playerRect.width - rect.left;
    float overlapx2 = rect.left + rect.width - playerRect.left;
    float overlapy1 = playerRect.top + playerRect.height - rect.top;
    float overlapy2 = rect.top + rect.height - playerRect.top;

    if (overlapx1 < 0 || overlapx2 < 0 || overlapy1 < 0 || overlapy2 < 0)
        return false;
    return true;
}

void Player::handleAllCollisions(std::vector<my_block>& blocks)
{
    mIsColliding = false;
    auto it = blocks.begin();
    bool del;
    sf::FloatRect ban;
    while (it != blocks.end())
    {
        del = false;
        if (handleCollision(*it)) {
            mIsColliding = true;
        }

        if(isattack && it->isdestr) {
            ban = it->mblock;
            ban.left -= 30;
            ban.width += 60;
            ban.top += 3;
            ban.height -=3;
            if(my_handleCollision(ban)) {
                if((mIsFacedRight && (mPosition.x < it->mblock.left)) || (!mIsFacedRight && (mPosition.x > (it->mblock.left + it->mblock.width))))
                    del = true;
            }
        }
        
        if(del)
            it = blocks.erase(it);
        else
            it++;
    }

    if (!mIsColliding)
        mpState->startFalling(this);
}


Player::~Player()
{
    delete mpState;
}
