#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "world.hpp"


/*
    Для компиляции:
         g++ main.cpp player.cpp player_states.cpp -lsfml-window -lsfml-system -lsfml-graphics

    Графика взята отсюда:
        https://rvros.itch.io/animated-pixel-hero
*/


int main() 
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Player states", sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    double time = 0;
    double dt = 1.0 / 60;

    World world;
    world.addBlock(sf::FloatRect{-500, 770, 20000, 400});
    world.addBlock(sf::FloatRect{-400, 100, 700, 300});
    world.addBlock(sf::FloatRect{600, 500, 300, 120});
    world.addBlock(sf::FloatRect{800, 0, 400, 200});
    world.addBlock(sf::FloatRect{-100, -700, 400, 100});
    world.addBlock(sf::FloatRect{700, -700, 400, 100});

    world.addBlock({sf::FloatRect{300, 400, 50, 370}, true});
    
    world.addBlock(sf::FloatRect{1500, -700, 400, 100});
    world.addBlock(sf::FloatRect{1100, -300, 400, 100});
    world.addBlock(sf::FloatRect{1100, 400, 400, 400});
    world.addBlock(sf::FloatRect{1900, -100, 200, 800});
    world.addBlock(sf::FloatRect{3000, 500, 1000, 200});


    while (window.isOpen()) 
    {
        sf::Event event;
        while(window.pollEvent(event)) 
        {
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) 
                window.close();

            world.handleEvents(event);
        }
        window.clear(sf::Color::Black);
        world.update(dt);
        world.draw(window);

        window.display();

        time += dt;
    }

    return 0;
}



