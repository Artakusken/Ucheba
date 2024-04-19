#pragma once


namespace ya {
    class Line {
        sf::Vertex line[2];
    public:
        Line() {
            line[0].position = sf::Vector2f(-1, -1);
            line[1].position = sf::Vector2f(-1, -1);
        }

        Line(float x_start, float y_start, float x_end, float y_end) {
            Setup(x_start, y_start, x_end, y_end);
        }

        void Setup(float x_start, float y_start, float x_end, float y_end){
            line[0].position = sf::Vector2f(x_start, y_start);
            line[1].position = sf::Vector2f(x_end, y_end);
        }

        sf::Vertex& getLine() {
            return *line;
        }
    };
}