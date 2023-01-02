#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Draggable
{
private:
    sf::RectangleShape mShape   {};
    sf::RectangleShape mFON   {};
    bool mIsDragged             {false};
    sf::Vector2f mOffset        {0.0f, 0.0f};
    int min_value {0};
    int max_value {10};
    float percent_value{0.0f};
    sf::Font font;
    sf::Text text;

public:
    Draggable() {};
    Draggable(const sf::RectangleShape& shape) : mShape{shape} {}
    Draggable(sf::Vector2f position, sf::Color color, int mi, int ma, float p) 
    {
        mShape.setPosition(position - sf::Vector2f{25, 25});
        mFON.setPosition(position);
        mShape.setSize({50, 100});
        mFON.setSize({500, 50});
        mShape.setFillColor(color);
        mFON.setFillColor({200, 200, 200});
        min_value = mi;
        max_value = ma;
        percent_value = p;
        if (!font.loadFromFile("consola.ttf"))
		std::cout << "Error loading font\n";
	text.setFont(font);
	text.setFillColor(color);
        text.setCharacterSize(30);
	text.setPosition(position + sf::Vector2f{550, 0});
	text.setString(std::to_string((int) percent_value * max_value / 100));
    }

    bool onMousePressed(sf::Vector2f mousePosition)
    {
        if (mShape.getGlobalBounds().contains(mousePosition))
        {
            mIsDragged = true;
            mOffset = mousePosition - mShape.getPosition();
        }
        else if (mFON.getGlobalBounds().contains(mousePosition))
        {
            mOffset = mousePosition - mShape.getPosition();
            mShape.setPosition(sf::Vector2f{mousePosition.x - 25, mFON.getPosition().y - 25});
        }
        return mIsDragged;
    }

    void onMouseReleased()
    {
        mIsDragged = false;
    }

    void onMouseMoved(sf::Vector2f mousePosition)
    {
        if (mIsDragged)
        {
            mShape.setPosition(mousePosition - mOffset);
        }
    }

    void setColor(sf::Color c)
    {
        mShape.setFillColor(c);
    }

    void setSize(sf::Vector2f sz)
    {
        mShape.setSize(sz);
    }

    void setPosition(sf::Vector2f sz)
    {
        mShape.setSize(sz);
    }

    void draw(sf::RenderWindow& rw) const
    {
        rw.draw(mFON);
        rw.draw(mShape);
        rw.draw(text);
    }
};



int main()
{
    sf::RenderWindow window(sf::VideoMode(1300, 650), "Slider");
    window.setFramerateLimit(60);


    Draggable ra {{50, 50}, sf::Color::White, 1, 100, 77};
    Draggable r {{50, 200}, sf::Color::Red, 0, 255, 25};
    Draggable g {{50, 350}, sf::Color::Green, 0, 255, 50};
    Draggable b {{50, 500}, sf::Color::Blue, 0, 255, 75};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                ra.onMousePressed(mousePosition);
                r.onMousePressed(mousePosition);
                g.onMousePressed(mousePosition);
                b.onMousePressed(mousePosition);
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                ra.onMouseReleased();
                r.onMouseReleased();
                g.onMouseReleased();
                b.onMouseReleased();
            }

            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
                ra.onMouseMoved(mousePosition);
                r.onMouseMoved(mousePosition);
                g.onMouseMoved(mousePosition);
                b.onMouseMoved(mousePosition);
            }
        }
        
        window.clear(sf::Color::Black);
        ra.draw(window);
        r.draw(window);
        g.draw(window);
        b.draw(window);
        window.display();
    }
}
