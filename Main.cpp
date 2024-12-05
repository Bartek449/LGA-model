#include <SFML/Window.hpp>
#include <GL/glew.h>
#include "Simulation.h"
#include <vector>

void updatePixelData(Simulation& simulation, std::vector<float>& vertices, int rows, int columns) {
    // Przypisanie miejsca na bufor
    vertices.clear();
    vertices.reserve(rows * columns * 12);

    const float pixelWidth = 2.0f / columns;
    const float pixelHeight = 2.0f / rows;

    for (int i = 0; i < rows; ++i) {
        float y = 1.0f - (float)i / rows * 2.0f;

        for (int j = 0; j < columns; ++j) {
            Cell cell = simulation.get_matrix().get_element(i, j);
            float color;
            if (cell.get_color() == 255) color = 1.0f;
            else if (cell.get_color() == 0) color = 0.0f;
            else color = 0.5f;
            float x = (float)j / columns * 2.0f - 1.0f;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(color);

            vertices.push_back(x + pixelWidth);
            vertices.push_back(y);
            vertices.push_back(color);

            vertices.push_back(x + pixelWidth);
            vertices.push_back(y - pixelHeight);
            vertices.push_back(color);

            vertices.push_back(x);
            vertices.push_back(y - pixelHeight);
            vertices.push_back(color);
        }
    }
}

int main() {
    int rows = 170, columns = 229;
    Simulation simulation(rows, columns);
    simulation.get_matrix();

    sf::Window window(sf::VideoMode(800, 600), "LGA Simulation", sf::Style::Default, sf::ContextSettings(24));
    glewInit();

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    std::vector<float> vertices;
    updatePixelData(simulation, vertices, rows, columns);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STREAM_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    GLuint shaderProgram = glCreateProgram();

    const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec2 aPos;
        layout(location = 1) in float aColor;

        out float color;

        void main() {
            gl_Position = vec4(aPos, 0.0, 1.0);
            color = aColor;
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        in float color;
        out vec4 FragColor;

        void main() {
            FragColor = vec4(color, color, color, 1.0);
        }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glAttachShader(shaderProgram, vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Space)
                    simulation.get_matrix().opening_gate();
            }
        }

        simulation.collision();
        simulation.streaming();
        updatePixelData(simulation, vertices, rows, columns);

        // Aktualizacja tylko zmieniających się danych w buforze
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_QUADS, 0, rows * columns * 4);

        window.display();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shaderProgram);

    return 0;
}
