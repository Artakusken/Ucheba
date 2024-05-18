#pragma once

#include <SFML/Graphics.hpp>

namespace ya {
    class LaserPulse {
        float x, y; // coords;
        float vel_x, vel_y; // velocity
        float scale;
    public:
        LaserPulse() {
            x = -20;
            y = -20;
            vel_x = 0;
            vel_y = 0;
            scale = 1;
        }

        LaserPulse(float x_cor, float y_cor, float velX, float velY) {
            Setup(x_cor, y_cor, velX, velY);
        }

        void Setup(float x_cor, float y_cor, float velX, float velY) {
            x = x_cor;
            y = y_cor;
            vel_x = velX;
            vel_y = velY;
            scale = 1;
        }

        void Destroy() {
            Setup(-20, -20, 0, 0);
        }

        void Move(float dt) {
            x += vel_x * dt;
            y += vel_y * dt;
        }

        bool BehindBorders(int x_border, int y_border) {
            if (x < 0 or x > x_border or y < 0 or y > y_border) {
                return true;
            }
            else {return false;}
        }

        void SuckInBH(float dist) {
            if (1000 / dist < 0.4) {
                scale = 1 - 1000 / dist;
            }
        }

        float getX() { return x; }
        float getY() { return y; }
        float getScale() { return scale; }

        void changeVelX(float dvx) { vel_x += dvx; }
        void changeVelY(float dvy) { vel_y += dvy; }
    };
}