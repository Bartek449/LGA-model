#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <GL/glew.h>
#include "Simulation.h"

int main() {
    int rows = 170, columns = 229;
    const int pixelSize = 3;  // Rozmiar pojedynczego piksela

    Simulation simulation(rows, columns);
    simulation.get_matrix();

    // Okno o rozmiarze dopasowanym do macierzy
    sf::RenderWindow window(sf::VideoMode(columns * pixelSize, rows * pixelSize), "LGA Simulation");

    // VertexArray do rysowania pikseli
    sf::VertexArray pixels(sf::Quads, rows * columns * 4);

    // Ustawienie pozycji wierzchołków (stała część)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            int index = (i * columns + j) * 4;

            float x = j * pixelSize;
            float y = i * pixelSize;

            // Przypisanie pozycji wierzchołków
            pixels[index].position = sf::Vector2f(x, y);
            pixels[index + 1].position = sf::Vector2f(x + pixelSize, y);
            pixels[index + 2].position = sf::Vector2f(x + pixelSize, y + pixelSize);
            pixels[index + 3].position = sf::Vector2f(x, y + pixelSize);
        }
    }

    // Funkcja do aktualizacji kolorów pikseli
    auto updatePixelColors = [&](Simulation& sim) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                Cell cell = sim.get_matrix().get_element(i, j);
                sf::Color color;

                // Kolor w zależności od wartości w komórce
                if (cell.get_color() == 255)
                    color = sf::Color::White;
                else if (cell.get_color() == 0)
                    color = sf::Color::Black;
                else
                    color = sf::Color(122, 122, 122);  // Szary

                // Obliczanie indeksu w tablicy wierzchołków
                int index = (i * columns + j) * 4;

                // Przypisanie koloru
                pixels[index].color = color;
                pixels[index + 1].color = color;
                pixels[index + 2].color = color;
                pixels[index + 3].color = color;
            }
        }
        };

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

        // Zaktualizuj kolory pikseli
        updatePixelColors(simulation);

        window.clear();  // Czyści ekran
        window.draw(pixels);  // Rysowanie pikseli
        window.display();  // Wyświetlenie nowego obrazu
    }

    return 0;
}
