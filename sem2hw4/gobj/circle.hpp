#pragma once
#include "cmath"

namespace ya {
    class Circle {
        float radius;
        float x, y;
        sf::CircleShape circleShape;
    public:
        Circle(){
            x = y = 0;
            radius = 0;
        };

        Circle(float x_cor, float y_cor, float r, float vel, int col) {
            Setup(x_cor, y_cor, r, vel, col);
        }

        void Setup(float x_cor, float y_cor, float r, float vel, int col) {
            x = x_cor;
            y = y_cor;
            radius = r;
            circleShape.setOrigin(radius, radius);
            circleShape.setRadius(radius);
            circleShape.setPosition(x, y);
            circleShape.setFillColor(sf::Color(20 * col, 20 * col, 240, 255));
        }

        sf::CircleShape getShape() {
            return circleShape;
        }

        float getRadius() {
            return radius;
        }

        float getX() {
            return x;
        }

        float getY() {
            return y;
        }
    };
}