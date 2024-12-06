#include <SFML/Window.hpp>
#include <GL/glew.h>
#include "Simulation.h"
#include <vector>


void checkShaderCompilation(GLuint shader, const std::string& shaderType) {
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        throw runtime_error(shaderType + " Shader Compilation Failed: " + (infoLog));
    }
}

void checkProgramLinking(GLuint program) {
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        throw runtime_error("Shader Program Linking Failed: " + string(infoLog));
    }
}

void updatePixelData(Simulation& simulation, std::vector<float>& vertices, int rows, int columns) {
    int c = 0;
    std::vector<float> newVertices;
    newVertices.reserve(rows * columns * 12);

    const float pixelWidth = 2.0f / columns;
    const float pixelHeight = 2.0f / rows;

    for (int i = 0; i < rows; ++i) {
        float y = 1.0f - static_cast<float>(i) / rows * 2.0f;

        for (int j = 0; j < columns; ++j) {
            Cell cell = simulation.get_matrix().get_element(i, j);
            float color;
            if (cell.get_color() == 255)  color = 1.0f;
            else if (cell.get_color() == 0) {
                color = 0.0f;
                c++;
            }
            else  color = 0.5f;
            float x = static_cast<float>(j) / columns * 2.0f - 1.0f;

            newVertices.insert(newVertices.end(), {
                x, y, color,
                x + pixelWidth, y, color,
                x + pixelWidth, y - pixelHeight, color,
                x, y - pixelHeight, color
                });
        }
    }
    cout << c << endl;
    vertices.swap(newVertices);
}

int main() {

    const int rows = 70, columns = 129;

    Simulation simulation(rows, columns);

    sf::Window window(sf::VideoMode(800, 600), "LGA Simulation", sf::Style::Default, sf::ContextSettings(24));
    glewInit();

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);


    vector<float> vertices;
    updatePixelData(simulation, vertices, rows, columns);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

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
    checkShaderCompilation(vertexShader, "Vertex");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompilation(fragmentShader, "Fragment");

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgramLinking(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);

    
    sf::Clock logic_clock, render_clock;
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

        
        if (logic_clock.getElapsedTime().asMilliseconds() >= 2) {
            logic_clock.restart();
            simulation.collision();
            simulation.streaming();
            updatePixelData(simulation, vertices, rows, columns);

            glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
        }

        if (render_clock.getElapsedTime().asMilliseconds() >= 1) { 
            render_clock.restart();
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawArrays(GL_QUADS, 0, rows * columns * 4);
            window.display();
        }
    }

    
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shaderProgram);

    return 0;
}
