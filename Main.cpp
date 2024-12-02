#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include"Simulation.h"




int main() {
    int rows = 170, columns = 229;
    Matrix M(rows, columns);
    const int pixelSize = 3;

    M.prepare_environment();
    

    sf::RenderWindow window(sf::VideoMode(columns * pixelSize, rows * pixelSize), "LGA Simulation");
    
    bool running = true;
    while (running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) running = false;
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) running = false;
                if (event.key.code == sf::Keyboard::Space) M.opening_gate();
            }
               
        }

        window.clear();

       
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                sf::RectangleShape pixel(sf::Vector2f(pixelSize, pixelSize));
                pixel.setPosition(j * pixelSize, i * pixelSize);

                int value = M.get_element(i, j).get_color();
                pixel.setFillColor(sf::Color(value, value, value));
                window.draw(pixel);
            }
        }

        window.display();
    }

    return 0;
}