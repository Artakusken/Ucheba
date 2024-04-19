#pragma once


namespace ya {
    class Rectangle {
        float x, y;
        float width, height;
        sf::RectangleShape rectangleShape;
    public:
        Rectangle(){
            x = y = 0;
            width = height = 0;
        };

        Rectangle(float x_cor, float y_cor, float rect_width, float rect_height) {
            Setup(x_cor, y_cor, rect_width, rect_height);
        }

        void Setup(float x_cor, float y_cor, float rect_width, float rect_height) {
            x = x_cor;
            y = y_cor;
            width = rect_width;
            height = rect_height;
            rectangleShape.setPosition(x, y);
            rectangleShape.setSize(sf::Vector2f(width, height));
            rectangleShape.setFillColor(sf::Color(194, 24, 64, 255));
        }

        sf::RectangleShape getShape() {
            return rectangleShape;
        }
    };
}