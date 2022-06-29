#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


float formula(float x, int height, float scale)
{
    return height * scale - (3 * pow(x, 4) + 4 * pow(x, 3) - 12 * pow(x, 2) - 5) * scale * 4;
}

// Функція для знаходження точки з найменшим значенням функції з проміжку
sf::Vector2f segment_min(float start, float finish)
{
    sf::Vector2f min(0.0,0.0);
    for(float i = start; i <= finish; i += 0.5)
    {
        float y = 3 * pow(i, 4) + 4 * pow(i, 3) - 12 * pow(i, 2) - 5;
        if(y < min.y)
        {
            min.x = i;
            min.y = y;
        }
    }
    return min;
}

// Функція для знаходження точки з найбільшим значенням функції з проміжку
sf::Vector2f segment_max(float start, float finish)
{
    sf::Vector2f max(0.0, 0.0);
    for(float i = start; i <= finish; i += 0.5)
    {
        float y = 3 * pow(i, 4) + 4 * pow(i, 3) - 12 * pow(i, 2) - 5;
        if(y > max.y)
        {
            max.x = i;
            max.y = y;
        }
    }
    return max;
}

// Функція для побудови клітин на графіку
void build_cells(int width, float scale, float start, float end, sf::RenderWindow& window)
{
    if(end >= 0 && start <= 0)
    {
        sf::Vertex vertical[2];
        for (int x = width * scale + end * scale * 8; x >= width * scale + start * scale * 8; x -= scale * 4)
        {
            vertical[0] = sf::Vertex(sf::Vector2f(x, width * scale - segment_max(start, end).y * scale * 4));
            vertical[1] = sf::Vertex(sf::Vector2f(x, width * scale - segment_min(start, end).y * scale * 4));
            vertical[0].color = sf::Color(75,75,75);
            vertical[1].color = sf::Color(75,75,75);
            window.draw(vertical, 2, sf::Lines);
        }
        if(segment_max(start, end).y >= 0 && segment_min(start, end).y <= 0)
        {
            sf::Vertex horyzontal[2];
            for(int y = width * scale - segment_max(start, end).y * scale * 4;
                y <= width * scale - segment_min(start, end).y * scale * 4; y += scale * 4)
            {
                horyzontal[0] = sf::Vertex(sf::Vector2f(width * scale + end * scale * 8, y));
                horyzontal[1] = sf::Vertex(sf::Vector2f(width * scale + start * scale * 8, y));
                horyzontal[0].color = sf::Color(75,75,75);
                horyzontal[1].color = sf::Color(75,75,75);
                window.draw(horyzontal, 2, sf::Lines);
            }
        }
    }
    else
    {
        sf::Vertex vertical[2];
        if(end > 0)
        {
            for (int x = width * scale + end * scale * 8; x >= width * scale; x -= scale * 4)
            {
                vertical[0] = sf::Vertex(sf::Vector2f(x, width * scale - segment_max(start, end).y * scale * 4));
                vertical[1] = sf::Vertex(sf::Vector2f(x, width * scale - segment_min(start, end).y * scale * 4));
                vertical[0].color = sf::Color(75,75,75);
                vertical[1].color = sf::Color(75,75,75);
                window.draw(vertical, 2, sf::Lines);
            }
            sf::Vertex horyzontal[2];
            for(int y = width * scale - segment_max(start, end).y * scale * 4; y <= width * scale - segment_min(start, end).y * scale * 4; y += scale * 4) {
                horyzontal[0] = sf::Vertex(sf::Vector2f(width * scale + end * scale * 8, y));
                horyzontal[1] = sf::Vertex(sf::Vector2f(width * scale, y));
                horyzontal[0].color = sf::Color(75, 75, 75);
                horyzontal[1].color = sf::Color(75, 75, 75);
                window.draw(horyzontal, 2, sf::Lines);
            }
        }
        else
        {
            for (int x = width * scale; x >= width * scale + start * scale * 8; x -= scale * 4)
            {
                vertical[0] = sf::Vertex(sf::Vector2f(x, width * scale - segment_max(start, end).y * scale * 4));
                vertical[1] = sf::Vertex(sf::Vector2f(x, width * scale - segment_min(start, end).y * scale * 4));
                vertical[0].color = sf::Color(75,75,75);
                vertical[1].color = sf::Color(75,75,75);
                window.draw(vertical, 2, sf::Lines);
            }
            sf::Vertex horyzontal[2];
            for(int y = width * scale - segment_max(start, end).y * scale * 4; y <= width * scale - segment_min(start, end).y * scale * 4; y += scale * 4)
            {
                horyzontal[0] = sf::Vertex(sf::Vector2f(width * scale + start * scale * 8, y));
                horyzontal[1] = sf::Vertex(sf::Vector2f(width * scale, y));
                horyzontal[0].color = sf::Color(75,75,75);
                horyzontal[1].color = sf::Color(75,75,75);
                window.draw(horyzontal, 2, sf::Lines);
        }

        }
    }
    }

// Функція для побудови цифр для позначення значення на поділці осі Х та Y
void build_numbers(int width, float scale, float start, float end, sf::RenderWindow& window)
{
    sf::Font font;
    if(!font.loadFromFile("../Arialn.ttf"))
    {
        std::cout << "Couldn't find the font!" << std::endl;
        return;
    }

    sf::Text number;
    number.setFont(font);
    number.setCharacterSize(9);

    if(end >= 0 && start <= 0)
    {
        for (int i = width * scale + start * scale * 8, j = -abs(start) * scale * 8 / 20;
             i <= width * scale + end * scale * 8; i += scale * 4, j++) {
            if (j == 0)
                continue;

            std::string num = std::to_string(static_cast<int>(j));
            number.setString(num);
            number.setPosition(sf::Vector2f(i - 3, width * scale + 5));
            number.setFillColor(sf::Color::Green);
            window.draw(number);
        }

    }
    else
    {
        if(end < 0)
        {
            for (int i = width * scale + start * scale * 8, j = start * scale * 8 / 20;
                 i <= width * scale; i += scale * 4, j++) {
                if (j == 0)
                    continue;

                std::string num = std::to_string(static_cast<int>(j));
                number.setString(num);
                number.setPosition(sf::Vector2f(i - 3, width * scale + 5));
                number.setFillColor(sf::Color::Green);
                window.draw(number);
            }
        }
        else
        {
            for (int i = width * scale, j = 0; i <= width * scale + end * scale * 8;
            i += scale * 4, j++)
            {
                if (j == 0)
                    continue;

                std::string num = std::to_string(static_cast<int>(j));
                number.setString(num);
                number.setPosition(sf::Vector2f(i - 3, width * scale + 5));
                number.setFillColor(sf::Color::Green);
                window.draw(number);
            }
        }
    }
    for(int i = width * scale - segment_max(start, end).y * scale * 4, j = segment_max(start, end).y;
        i <= width * scale - segment_min(start, end).y * scale * 4; i += scale * 4, j--)
    {
        if (j == 0)
            continue;

        std::string num = std::to_string(static_cast<int>(j));
        number.setString(num);
        number.setPosition(sf::Vector2f(width * scale + 5, i - 5));
        number.setFillColor(sf::Color::Cyan);
        window.draw(number);
    }
}

// Функція для побудови осей X та Y
void build_axe(char axe, float start, float end, int width, float scale, sf::RenderWindow& window)
{
    if(axe == 'x')
    {
        sf::Vertex xAxe[2];
        if (start <= 0 && end >= 0)
        {
            xAxe[0] = {sf::Vertex(sf::Vector2f(width * scale + start * scale * 8, width * scale))};
            xAxe[1] = {sf::Vertex(sf::Vector2f(width * scale + end * scale * 8, width * scale))};
        }
        else if (end > 0)
        {
            xAxe[0] = {sf::Vertex(sf::Vector2f(width * scale, width * scale))};
            xAxe[1] = {sf::Vertex(sf::Vector2f(width * scale + end * scale * 8, width * scale))};
        }
        else
        {
            xAxe[0] = {sf::Vertex(sf::Vector2f(width * scale, width * scale))};
            xAxe[1] = {sf::Vertex(sf::Vector2f(width * scale + start * scale * 8, width * scale))};
        }


        window.draw(xAxe, 2, sf::Lines);
    }

    if(axe == 'y')
    {
        sf::Vertex yAxe[2];
        if(segment_max(start, end).y >= 0 && segment_min(start, end).y <= 0)
        {
             yAxe[0] = {sf::Vertex(sf::Vector2f(width * scale, width * scale - segment_max(start, end).y * scale * 4))};
             yAxe[1] = {sf::Vertex(sf::Vector2f(width * scale, width * scale - segment_min(start, end).y * scale * 4))};
        }
        else
        {
            yAxe[0] = {sf::Vertex(sf::Vector2f(width * scale, width * scale))};
            yAxe[1] = {sf::Vertex(sf::Vector2f(width * scale, width * scale - segment_max(start, end).y))};
        }
        window.draw(yAxe, 2, sf::Lines);
    }
}

// Функція для побудови поділок
void build_divs(int width, float scale, float start, float end, sf::RenderWindow& window)
{
    sf::VertexArray yDivs(sf::LineStrip);
    sf::VertexArray xDivs(sf::LineStrip);

    if(start <= 0 && end >= 0)
    {
        for (int x = width * scale + end * scale * 8; x >= width * scale + start * scale * 8; x -= scale * 4)
        {
            if(x == width * scale)
                continue;

            float tempY1 = width * scale - 3;
            float tempY2 = width * scale + 3;
            xDivs.append(sf::Vertex(sf::Vector2f(x, tempY1)));
            xDivs.append(sf::Vertex(sf::Vector2f(x, tempY2)));
            window.draw(xDivs);
            xDivs.clear();
        }
    }
    else

        if(end > 0)
        {
            for (int x = width * scale + end * scale * 8; x >= width * scale; x -= scale * 4)
            {
                if (x == width * scale)
                    continue;

                float tempY1 = width * scale - 3;
                float tempY2 = width * scale + 3;
                xDivs.append(sf::Vertex(sf::Vector2f(x, tempY1)));
                xDivs.append(sf::Vertex(sf::Vector2f(x, tempY2)));
                window.draw(xDivs);
                xDivs.clear();
            }
        }
        else
        {
            for (int x = width * scale; x >= width * scale + start * scale * 8; x -= scale * 4)
            {
                if (x == width * scale)
                    continue;

                float tempY1 = width * scale - 3;
                float tempY2 = width * scale + 3;
                xDivs.append(sf::Vertex(sf::Vector2f(x, tempY1)));
                xDivs.append(sf::Vertex(sf::Vector2f(x, tempY2)));
                window.draw(xDivs);
                xDivs.clear();
            }
        }

    if(segment_max(start, end).y >= 0 && segment_min(start, end).y <= 0)
    {
        for (int y = width * scale - segment_max(start, end).y * scale * 4;
             y <= width * scale - segment_min(start, end).y * scale * 4; y += scale * 4)
        {
            if (y == width * scale)
                continue;

            float tempX1 = width * scale - 3;
            float tempX2 = width * scale + 3;
            yDivs.append(sf::Vertex(sf::Vector2f(tempX1, y)));
            yDivs.append(sf::Vertex(sf::Vector2f(tempX2, y)));
            window.draw(yDivs);
            yDivs.clear();
        }
    }
    else
    {
        for (int y = width * scale;
             y <= width * scale - segment_min(start, end).y * scale * 4; y += scale * 4)
        {
            if(y == width * scale)
                continue;

            float tempX1 = width * scale - 3;
            float tempX2 = width * scale + 3;
            yDivs.append(sf::Vertex(sf::Vector2f(tempX1, y)));
            yDivs.append(sf::Vertex(sf::Vector2f(tempX2, y)));
            window.draw(yDivs);
            yDivs.clear();
        }
    }
}

// Функція для побудови графіка
void build_plot(int width, float scale, float start, float end, sf::RenderWindow& window)
{
    sf::VertexArray plot(sf::LinesStrip);
    for(float i = start; i < end; i += 0.1f)
    {
        sf::Vertex vrtx = sf::Vertex(sf::Vector2f(width * scale + i * scale * 4, formula(i, width, scale)));
        vrtx.color = sf::Color::Red;

        plot.append(vrtx);
    }
    window.draw(plot);
}

int main()
{
    int windowWidth = 1280;
    int windowHeight = 720;
    float scale = 5.f;
    float kMover = 15.f;

    // Введення області визначення
    float start;
    float end;
    std::cout << "Enter the segment borders: " << std::endl;
    std::cin >> start >> end;
    while(start >= end)
    {
        std::cout << "Initial x must be lower than the last one or equal to it!\n";
        std::cout << "Enter the segment borders: " << std::endl;
        std::cin >> start >> end;
    }

    // Створення вікна
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Graph");
    sf::Vector2u windowSize = window.getSize();

    // Створення камери
    sf::View camera = sf::View(sf::Vector2f(windowSize.x * scale, windowSize.x * scale),
                               sf::Vector2f(windowSize.x / 2, windowSize.y / 2));

    // Робота вікна забезпечується циклом, який перевіряє чи вікно досі відкрите
    while (window.isOpen())
    {
        // Обробник подій перевіряє все, що робить користувач у вікні
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                // Подія закриття вікна
                case sf::Event::Closed:
                    window.close();
                    break;
                // Подія рухання колеса миші
                case sf::Event::MouseWheelMoved:
                // Якщо колесо крутиться вперед, то зменшуємо масштаб і зменшуємо швидкість зсуву камери
                    if(event.mouseWheel.delta > 0)
                    {
                        camera.zoom(0.95f);
                        if(kMover > 1)
                            kMover -= 0.6;
                    }
                // Якщо назад - навпаки - збільшуємо масштаб і швидкість зсуву
                    else
                    {
                        camera.zoom(1.05f);
                        kMover += 0.7;
                    }
                // Подія натискання клавіші
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        // Якщо натиснута латинська А - рухаємо камеру вліво
                        case sf::Keyboard::A:
                            camera.move(-kMover, 0.f);
                            break;
                        // Якщо натиснута латинська W - рухаємо камеру вверх
                        case sf::Keyboard::W:
                            camera.move(0.f, -kMover);
                            break;
                        // Якщо натиснута латинська S - рухаємо камеру вниз
                        case sf::Keyboard::S:
                            camera.move(0.f, kMover);
                            break;
                        // Якщо натиснута латинська D - рухаємо камеру вправо
                        case sf::Keyboard::D:
                            camera.move(kMover, 0.f);
                            break;
                    }
            }
        }
        // Очищуємо вікно, встановлюємо камеру і будуємо всі графічні елементи
        window.clear();
        window.setView(camera);
        build_cells(windowWidth, scale, start, end, window);
        build_axe('x', start, end, windowWidth, scale, window);
        build_axe('y', start, end, windowWidth, scale, window);
        build_numbers(windowWidth, scale, start, end, window);
        build_divs(windowWidth, scale, start, end, window);
        build_plot(windowWidth, scale, start, end, window);
        window.display();
    }

    return 0;
}
