#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;


struct Ball
{
    float radius;
    float mass;
    sf::Vector2f position;
    sf::Vector2f velocity;
};

int main()
{
    srand(time(0));
    
    const int width = 1000;
    const int height = 600;
    const int n_balls = 10;
    const float G = 1;

    // Шаг по времени
    const float delta_t = 0.1;

    // Создаём экземпляр класса окно
    sf::RenderWindow window(sf::VideoMode(width, height), "My window");
    // Задаём максимальное количество кадров в секунду
    window.setFramerateLimit(60);

    // Так как sf::CircleShape занимает много памяти, создаём всего 1 экземпляр
    sf::CircleShape circle(50.0f);
    circle.setFillColor({200, 216, 200});

    std::vector<Ball> balls;
    balls.resize(n_balls);
    for (int i = 0; i < n_balls; i++)
    {
        balls[i].radius = 4 + rand() % 8;
        balls[i].mass = balls[i].radius * balls[i].radius;
        balls[i].position = {(float)(rand() % width), (float)(rand() % height)};
        balls[i].velocity = {(float)(rand() % 100 - 50), (float)(rand() % 100 - 50)};
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // В данном примере проверяем окно на закрытие
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // очистить скрытый холст черным цветом
        window.clear(sf::Color::Black);

        for (int i = 0; i < n_balls; i++)
        {
            balls[i].position += balls[i].velocity * delta_t;

            /*
            if (balls[i].position.x < 0)
                balls[i].position.x += width;
            if (balls[i].position.x > width)
                balls[i].position.x -= width;

            if (balls[i].position.y < 0)
                balls[i].position.y += height;
            if (balls[i].position.y > height)
                balls[i].position.y -= height;
            */

            if (balls[i].position.x < 0 || balls[i].position.x > width)
                balls[i].velocity.x *= -1;
            if (balls[i].position.y < 0 || balls[i].position.y > height)
                balls[i].velocity.y *= -1;

            for(int myi = 0; myi < n_balls; myi++) {
                for(int myj = 0; myj < n_balls; myj++) {
                    if(myi == myj) {
                        continue;
                    }
                    float dist = std::sqrt((balls[myi].position.x - balls[myj].position.x) * (balls[myi].position.x - balls[myj].position.x) + (balls[myi].position.y - balls[myj].position.y) * (balls[myi].position.y - balls[myj].position.y));
                    auto path = balls[myi].position - balls[myj].position;
                    balls[myi].velocity -= (path * G * delta_t * balls[myj].mass) / (dist * dist);
                }
            }
            
            // Используем 1 sf::CircleShape, чтобы нарисовать все шары
            circle.setRadius(balls[i].radius);
            // setOrigin - задаёт центр объекта
            // По умолчанию центр - в левом верхнем угле объекта
            // Строка ниже устанавливает центр в центре шарика
            // В дальнейшем функция, setPosition устанавливает положение шарика так, 
            // чтобы его центр был в точке balls[i].position
            circle.setOrigin(balls[i].radius, balls[i].radius);
            circle.setPosition(balls[i].position);
            
            window.draw(circle);
        }

        // отображаем содержимое скрытого холста на экран
        window.display();
    }

    return 0;
}
