#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "player.hpp"
#include "player_states.hpp"
#include "block.hpp"




class World
{
public:

    void addBlock(my_block block)
    {
        mBlocks.push_back(block);
    }

    void setView()
    {
        sf::Vector2f playerCenter = mPlayer.getCenter();
        float mViewRatio = 0.6;
        if (playerCenter.x > mView.getCenter().x + mViewRatio * mView.getSize().x / 2)
            mView.move({playerCenter.x - mView.getCenter().x - mViewRatio * mView.getSize().x / 2, 0});

        else if (playerCenter.x < mView.getCenter().x - mViewRatio * mView.getSize().x / 2)
            mView.move({playerCenter.x - mView.getCenter().x + mViewRatio * mView.getSize().x / 2, 0});


        if (playerCenter.y > mView.getCenter().y + mViewRatio * mView.getSize().y / 2)
            mView.move({0, playerCenter.y - mView.getCenter().y - mViewRatio * mView.getSize().y / 2});

        else if (playerCenter.y < mView.getCenter().y - mViewRatio * mView.getSize().y / 2)
            mView.move({0, playerCenter.y - mView.getCenter().y+ mViewRatio * mView.getSize().y / 2});

    }

    void update(float dt)
    {   
        setView();
        mPlayer.applyVelocity({0, mGravity * dt});
        mPlayer.update(dt);
        mPlayer.handleAllCollisions(mBlocks);
    }

    void draw(sf::RenderWindow& window)
    {
        static sf::RectangleShape blockShape;
        blockShape.setFillColor(sf::Color(58, 69, 55));

        window.setView(mView);

        for (const my_block& b : mBlocks)
        {
            if(b.isdestr) {
                blockShape.setFillColor(sf::Color::Red);
            }
            blockShape.setPosition(b.mblock.left, b.mblock.top);
            blockShape.setSize({b.mblock.width, b.mblock.height});
            window.draw(blockShape);
            if(b.isdestr) {
                blockShape.setFillColor(sf::Color(58, 69, 55));
            }
        }
        mPlayer.draw(window);
    }

    void handleEvents(const sf::Event& event)
    {
        mPlayer.handleEvents(event);
    }



private:
    std::vector<my_block> mBlocks  {};
    Player mPlayer                      {{400, 400}};
    float mGravity                      {3600};

    sf::View mView                      {sf::FloatRect(0, 0, 1200, 900)};
};
