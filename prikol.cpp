#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int main()
{
    srand(time(0));
    
    const int width = 1000;
    const int height = 600;
    const float radius = 50.0f;
    const int speedrun = 10;
    const int sdvig = 5;
    const int probability = 2;
    float score = 0.0f;
    const float d_score = 0.01f;
    
    sf::RenderWindow window(sf::VideoMode(width, height), "My window");
    window.setFramerateLimit(60);

    sf::CircleShape circle(radius);
    circle.setFillColor({200, 216, 200});
    circle.setOrigin(radius, radius);
    circle.setPosition(sf::Vector2f{width / 2, height / 2});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    circle.setFillColor({rand()%256, rand()%256, rand()%256});
                }
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            circle.move(sf::Vector2f{0, -1 * speedrun});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            circle.move(sf::Vector2f{-1 * speedrun, 0});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            circle.move(sf::Vector2f{0, speedrun});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            circle.move(sf::Vector2f{speedrun, 0});
        }
        
        circle.move(sf::Vector2f{rand()%2 ? speedrun * (rand()%2) / 2 : - 1 * speedrun * (rand()%2) / 2, rand()%2 ? speedrun * (rand()%2) / 2 : - 1 * speedrun * (rand()%2) / 2});
        if(!(rand() % probability)) {
            circle.setFillColor({rand()%256, rand()%256, rand()%256});
            circle.move(sf::Vector2f{rand()%2 ? speedrun * (rand()%2) * sdvig : - 1 * speedrun * (rand()%2) * sdvig, rand()%2 ? speedrun * (rand()%2) * sdvig : - 1 * speedrun * (rand()%2) * sdvig});
        }

        score += d_score;
        if(circle.getPosition().x < 0 || circle.getPosition().x > width || circle.getPosition().y < 0 || circle.getPosition().y > height) {
            cout << score;
            window.close();
        }
            
        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

    return 0;
}
