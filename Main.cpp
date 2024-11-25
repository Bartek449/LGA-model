#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include"Matrix.h"




int main() {
    int rows = 150, columns = 209;
    Matrix M(rows, columns);
    const int pixelSize = 5;

    M.prepare_environment();
    

    sf::RenderWindow window(sf::VideoMode(columns * pixelSize, rows * pixelSize), "LGA Simulation");
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

       
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                sf::RectangleShape pixel(sf::Vector2f(pixelSize, pixelSize));
                pixel.setPosition(j * pixelSize, i * pixelSize);

                int value = M.get_element(i, j);
                pixel.setFillColor(sf::Color(value, value, value));
                window.draw(pixel);
            }
        }

        window.display();
    }

    return 0;
}