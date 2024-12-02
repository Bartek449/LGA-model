#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include"Simulation.h"

int main() {
    int rows = 170, columns = 229;
 
    const int pixelSize = 3;

    Simulation simulation(rows,columns);
    simulation.get_matrix().prepare_environment();
    
    sf::RenderWindow window(sf::VideoMode(columns * pixelSize, rows * pixelSize), "LGA Simulation");
    
    bool running = true;
    while (running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) running = false;
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) running = false;
                if (event.key.code == sf::Keyboard::Space) simulation.get_matrix().opening_gate();
            }
               
        }

        simulation.collision();
        simulation.streaming();


        window.clear();

        for (int i = 0; i < simulation.get_matrix().get_rows_num(); ++i) {
            for (int j = 0; j < simulation.get_matrix().get_columns_num(); ++j) {
                
                Cell cell = simulation.get_matrix().get_element(i, j);

                
                sf::RectangleShape pixel(sf::Vector2f(pixelSize, pixelSize));
                pixel.setPosition(j * pixelSize, i * pixelSize);

                
                if (cell.get_color() == 255)
                    pixel.setFillColor(sf::Color::White); 
                else if (cell.get_color() == 0)
                    pixel.setFillColor(sf::Color::Black); 
                else
                    pixel.setFillColor(sf::Color(122, 122, 122));

                
                window.draw(pixel);
            }
        }

        

        window.display();
    }

    return 0;
}