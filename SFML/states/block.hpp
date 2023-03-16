#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

struct my_block
{

    my_block(sf::FloatRect block, bool destr) {
        mblock = block;
        isdestr = destr;
    }

    my_block(sf::FloatRect block) {
        mblock = block;
        isdestr = false;
    }

    sf::FloatRect mblock;
    bool isdestr;
};
