#pragma once

#include <SFML/Graphics.hpp>
#include "cmath"

namespace ya {
    class Circle {
        float radius;
        float x, y;
        float v;
        float vel_x, vel_y;
        sf::CircleShape circleShape;
    public:
        Circle() {
            x = y = 0;
            radius = 0;
            vel_x = vel_y = 0;
        };

        Circle(float x_cor, float y_cor, float r, float vel, float alfa) {
            Setup(x_cor, y_cor, r, vel, alfa);
        }

        void Setup(float x_cor, float y_cor, float r, float vel, float alfa) {
            x = x_cor;
            y = y_cor;
            radius = r;
            v = vel;
            vel_x = v * cosf(alfa);
            vel_y = v * sinf(alfa);
            circleShape.setOrigin(radius, radius);
            circleShape.setRadius(radius);
            circleShape.setPosition(x, y);
            circleShape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
        }

        sf::CircleShape getShape() {
            return circleShape;
        }
        float getX() { return x; }
        float getY() { return y; }
        float getR() { return radius; }
        float getVelX() { return vel_x; }
        float getVelY() { return vel_y; }
        void setVelX(float vx) { vel_x = vx; }
        void setVelY(float vy) { vel_y = vy; }
        void InverseVelX() { vel_x = -vel_x; }
        void InverseVelY() { vel_y = -vel_y; }

        void Move(float dt) {
            x += vel_x * dt;
            y += vel_y * dt;
            circleShape.setPosition(x, y);
        }
    };

}