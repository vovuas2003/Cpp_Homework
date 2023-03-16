#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player_states.hpp"
#include "block.hpp"

class PlayerState;

class Player
{
public:

    Player(sf::Vector2f position);

    sf::Vector2f getCenter() const;
    void applyVelocity(sf::Vector2f velocity);

    void update(float dt);
    void draw(sf::RenderWindow& window);
    void handleEvents(const sf::Event& event);
    bool handleCollision(const my_block& rect);
    bool my_handleCollision(const my_block& rect);
    void handleAllCollisions(std::vector<my_block>& blocks);

    ~Player();

    friend class PlayerState;
    friend class Idle;
    friend class Running;
    friend class Falling;
    friend class Sliding;
    friend class Hooked;
    friend class Sitting;
    friend class FirstAttack;
    friend class SecondAttack;
    friend class ThirdAttack;

    int djump = 0;
    int nattack = 0;
    int isattack = 0;


private:

    sf::Vector2f    mPosition           {0, 0};
    sf::Vector2f    mVelocity           {0, 0};

    bool            mIsColliding        {false};     
    sf::FloatRect   mCollisionRect      {-40, -60, 80, 120};

    PlayerState*    mpState             {nullptr};
    sf::Texture     mTexture            {};
    sf::Sprite      mSprite             {}; 
    float           mScaleFactor        {1};
    bool            mIsFacedRight       {true};
    
    
    void setState(PlayerState* pNewState);
};
