#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Slider
{
private:
    sf::RectangleShape mShape   {};
    sf::RectangleShape mFON   {};
    bool mIsDragged             {false};
    int min_value;
    int max_value;
    float percent_value;
    int value;
    sf::Font font;
    sf::Text text;
    int dlina;
    int diff;
public:
    Slider(sf::Vector2f position, int d, sf::Color color, int mi, int ma, float p) 
    {
        mShape.setPosition(position - sf::Vector2f{25, 25});
        mFON.setPosition(position);
        mShape.setSize({50, 100});
        mFON.setSize({d, 50});
        dlina = d;
        mShape.setFillColor(color);
        mFON.setFillColor({200, 200, 200});
        min_value = mi;
        max_value = ma;
        percent_value = p;
        value = (int) (min_value + ((percent_value * (max_value - min_value)) / 100));
        mShape.move({(p * d) / 100, 0});
        if (!font.loadFromFile("consola.ttf"))
		std::cout << "Error loading font\n";
	text.setFont(font);
	text.setFillColor(color);
        text.setCharacterSize(30);
	text.setPosition(position + sf::Vector2f{d + 50, 0});
	text.setString(std::to_string(value));
    }

    bool onMousePressed(sf::Vector2f mousePosition)
    {
        if (mShape.getGlobalBounds().contains(mousePosition))
        {
            mIsDragged = true;
            diff = mousePosition.x - mShape.getPosition().x;
        }
        else if (mFON.getGlobalBounds().contains(mousePosition))
        {
            mIsDragged = true;
            diff = 25;
            mShape.setPosition(sf::Vector2f{mousePosition.x - 25, mFON.getPosition().y - 25});
            percent_value = ((mousePosition.x - mFON.getPosition().x) * 100) / dlina;
            value = (int) (min_value + ((percent_value * (max_value - min_value)) / 100));
            text.setString(std::to_string(value));
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
            sf::Vector2f temp = {mousePosition.x - diff, mFON.getPosition().y - 25};
            if (mousePosition.x - diff + 25 < mFON.getPosition().x)
                temp.x = mFON.getPosition().x - 25;
            if (mousePosition.x - diff + 25 > (mFON.getPosition().x + dlina))
                temp.x = mFON.getPosition().x - 25 + dlina;
            mShape.setPosition(temp);
            percent_value = ((mousePosition.x - diff + 25 - mFON.getPosition().x) * 100) / dlina;
            if (percent_value < 0)
                percent_value = 0;
            if (percent_value > 100)
                percent_value = 100;
            value = (int) (min_value + ((percent_value * (max_value - min_value)) / 100));
            text.setString(std::to_string(value));
        }
    }
    int get_value() {return value;}
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


    Slider ra {{50, 50}, 1000, sf::Color::White, 25, 100, 0};
    Slider r {{50, 200}, 500, sf::Color::Red, 0, 255, 25};
    Slider g {{50, 350}, 500, sf::Color::Green, 0, 255, 50};
    Slider b {{50, 500}, 500, sf::Color::Blue, 0, 255, 75};

    sf::CircleShape circle(2 * ra.get_value());
    circle.setFillColor({r.get_value(), g.get_value(), b.get_value()});
    circle.setOrigin(2 * ra.get_value(), 2 * ra.get_value());
    circle.setPosition(sf::Vector2f{1000, 375});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) 
            {
                window.close();
            }
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
        circle.setRadius(2 * ra.get_value());
        circle.setFillColor({r.get_value(), g.get_value(), b.get_value()});
        circle.setOrigin(2 * ra.get_value(), 2 * ra.get_value());
        circle.setPosition(sf::Vector2f{1000, 375});
        window.clear(sf::Color::Black);
        ra.draw(window);
        r.draw(window);
        g.draw(window);
        b.draw(window);
        window.draw(circle);
        window.display();
    }
}
