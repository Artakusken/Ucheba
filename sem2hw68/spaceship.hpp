#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "cmath"
#include "enemys.hpp"
#include "particles.hpp"


namespace ya {
    class Spaceship {
        float x, y; // coords
        float w, h; // ship size
        float vel_x, vel_y; // velocity
        float angle;  // degrees
        float target_angle;  // degrees

        bool px, mx, py, my;  // speed change (px - plus x, mx - minus x)
        bool to_stop; 
        bool faster;
        bool rotate_cw, rotate_acw;  // cw - clockwise, acw - anti-clockwise
        bool destroyed;

        sf::RectangleShape rectangleShape;
        sf::Texture shipTexture;
        sf::Sprite shipSprite;

        const float ACCELERATION = 0.004;
        const float ROTATION_SPEED = 2;
    public:
        Spaceship() {
            x = y = 200;
            vel_x = vel_y = 0;
        };

        Spaceship(float x_cor, float y_cor, float scale) {
            Setup(x_cor, y_cor, scale);
        }

        void Setup(float x_cor, float y_cor, float scale) {
            x = x_cor;
            y = y_cor;
            angle = 0;
            target_angle = 0;
            w = 50;
            h = 50;
            px = py = mx = my = false;
            rotate_cw = rotate_acw = to_stop = false;
            destroyed = false;

            if (!shipTexture.loadFromFile("..\\images\\battleship.png")) {
                rectangleShape.setPosition(x, y);
                rectangleShape.setSize(sf::Vector2(w, h));
                rectangleShape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
                std::cout << "Error while loading spaceship texture" << std::endl;
            }
            else {
                shipSprite.setTexture(shipTexture);
                shipTexture.setSmooth(true);
                shipSprite.setScale(0.5f, 0.5f);
                w = shipSprite.getTextureRect().getSize().x * shipSprite.getScale().x;
                h = shipSprite.getTextureRect().getSize().y * shipSprite.getScale().y;
                std::cout << w << std::endl;

                shipSprite.setPosition(x, y);
                shipSprite.setOrigin(w, h);
            }
        }

        void Move(float dt) {
            x += vel_x * dt;
            y += vel_y * dt;
            rectangleShape.setPosition(x, y);
            shipSprite.setPosition(x, y);

//            Rotate();
            shipSprite.setRotation(angle);
        }

        void BorderCheck(int win_w, int win_h, int more_space) {

            // X0 + abs(w/2 * cos(a)) + abs(h/2 * sin(a)) - самое крайнее правое положение
            // X0 - abs(w/2 * cos(a)) - abs(h/2 * sin(a)) - самое крайнее левое положение и т.п. для верха и низа
            if (x + std::abs((w / 2) * cosf(angle * acos(-1) / 180))
                + std::abs((h / 2) * sinf(angle * acos(-1) / 180)) >= win_w + more_space and vel_x > 0) { InverseVelX(vel_x / 1.5f);}
            else if (x - std::abs((w / 2) * cosf(angle * acos(-1) / 180))
                     - std::abs((h / 2) * sinf(angle * acos(-1) / 180)) <= 0 - more_space and vel_x < 0) { InverseVelX(vel_x / 1.5f); }
            if (y - std::abs((h / 2) * cosf(angle * acos(-1) / 180))
                - std::abs((w / 2) * sinf(angle * acos(-1) / 180)) <= 0 - more_space and vel_y < 0) { InverseVelY(vel_y / 1.5f); }
            else if (y + std::abs((h / 2) * cosf(angle * acos(-1) / 180))
                     + std::abs((w / 2) * sinf(angle * acos(-1) / 180)) >= win_h + more_space and vel_y > 0) { InverseVelY(vel_y / 1.5f); }
        }

        bool Shoot(ya::LaserPulse* lasers_array, unsigned short n_of_lasers) {
            if (n_of_lasers < 39) {
                float radians = angle * acos(-1) / 180;
                lasers_array[n_of_lasers].Setup(x + w / 2.5 * cosf(radians), y + w / 2.5 * sinf(radians),
                                                cosf(radians) * 0.5 + vel_x, sinf(radians) * 0.5 + vel_y);
                return true;
            }
            else { return false; }
        }

        void Rotate() {
            if (rotate_cw) {angle += ROTATION_SPEED;}
            if (rotate_acw)  {angle -= ROTATION_SPEED; }
//            std::cout << "cos " << cosf(angle * acos(-1) / 180) << " sin " << sinf(angle * acos(-1) / 180) << std::endl;
        }

        void RotateWithMouse(sf::RenderWindow* win) {
            target_angle = atan2(sf::Mouse::getPosition(*win).y - y, sf::Mouse::getPosition(*win).x - x) * 180 / acos(-1);
//            std::cout << "angle " << angle << " target angle " << target_angle << std::endl;
            if (abs(angle - target_angle) < 180) {
                if (angle > target_angle) { angle -= ROTATION_SPEED; }
                else if (angle < target_angle) { angle += ROTATION_SPEED; }

                if (abs(angle - target_angle) < 5) {angle = target_angle;}
            }
            else {
                if (angle > target_angle) { angle += ROTATION_SPEED; }
                else { angle -= ROTATION_SPEED; }
                if (angle > 180) {angle = -180;}
                else if (angle < -180) {angle = 180;}
            }
        }

        void SuckInBH(float dist) {
            if (1000 / dist < 0.4) {
                shipSprite.setScale(0.5f - 1000 / dist, 0.5f - 1000 / dist);
                w = shipSprite.getTextureRect().getSize().x * shipSprite.getScale().x;
                h = shipSprite.getTextureRect().getSize().y * shipSprite.getScale().y;
                shipSprite.setOrigin(w, h);
            }
        }

        void StartRotation(bool clockwise) {
            if (clockwise) {rotate_cw = true;}
            else {rotate_acw = true;}
        }

        void EndRotation(bool clockwise) {
            if (clockwise) { rotate_cw = false; }
            else { rotate_acw = false; }
        }

        void accelerate() {
            if (faster) {
                if (px) {vel_x += ACCELERATION * 2;}
                if (mx) {vel_x -= ACCELERATION * 2;}
                if (py) {vel_y += ACCELERATION * 2;}
                if (my) {vel_y -= ACCELERATION * 2;}
            } else {
                if (px) {vel_x += ACCELERATION;}
                if (mx) {vel_x -= ACCELERATION;}
                if (py) {vel_y += ACCELERATION;}
                if (my) {vel_y -= ACCELERATION;}
            }
        }

        void decelerate() {
            if (to_stop) {
                if (vel_x < 0) { vel_x += ACCELERATION; }
                if (vel_x > 0) { vel_x -= ACCELERATION; }
                if (vel_y < 0) { vel_y += ACCELERATION; }
                if (vel_y > 0) { vel_y -= ACCELERATION; }
                if (std::abs(vel_x) < 0.01 and std::abs(vel_y) < 0.01) {
                    vel_x = 0;
                    vel_y = 0;
                    to_stop = false;
                }
            }
        }

        sf::RectangleShape getShape() {
            return rectangleShape;
        }

        sf::Sprite getSprite() {
            return shipSprite;
        }

        float getX() { return x; }
        float getY() { return y; }
        float getW() { return w; }
        float getH() { return h; }
        float getVelX() { return vel_x; }
        float getVelY() { return vel_y; }
        float getAlpha() {return angle; }
        float isDestroyed() { return destroyed; }

        void Destroy() {destroyed = true;}
        void setVelPX(bool vx) { px = vx; }
        void setVelMX(bool vx) { mx = vx; }
        void setVelPY(bool vy) { py = vy; }
        void setVelMY(bool vy) { my = vy; }
        void setStop(bool vy) { to_stop = vy; }
        void setFaster(bool vy) { faster = vy; }
        void changeVelX(float dvx) { vel_x += dvx; }
        void changeVelY(float dvy) { vel_y += dvy; }
        void InverseVelX(float diff=0) { vel_x = -vel_x + diff; }
        void InverseVelY(float diff=0) { vel_y = -vel_y + diff; }
    };
}