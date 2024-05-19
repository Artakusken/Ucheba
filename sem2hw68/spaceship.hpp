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

        float col_corsx[12];
        float col_corsy[12];

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

                shipSprite.setPosition(x, y);
                shipSprite.setOrigin(w, h);
            }
        }

        void Destroy() {
            destroyed = true;
            x = y = -500;
            vel_x = vel_y = 0;
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

        void CalculateCollision() {
            float angle_cos = cosf(angle * acos(-1) / 180);
            float angle_sin = sinf(angle * acos(-1) / 180);
            col_corsx[0] = x - w / 4 * angle_cos + h / 2 * angle_sin;  // верхняя линия 1
            col_corsy[0] = y - h / 2 * angle_cos - w / 4 * angle_sin;  // верхняя линия 1

            col_corsx[1] = x + w / 4 * angle_cos + h / 2 * angle_sin;  // верхняя линия 2
            col_corsy[1] = y - h / 2 * angle_cos + w / 4 * angle_sin;  // верхняя линия 2

            col_corsx[2] = x + h / 2.5f * angle_sin;  // верхняя линия 3 (верхняя середина)
            col_corsy[2] = y - h / 2.5f * angle_cos;  // верхняя линия 3 (верхняя середина)

            col_corsx[3] = x + w / 4 * angle_cos - h / 2 * angle_sin;  // нижняя линия 1
            col_corsy[3] = y + h / 2 * angle_cos + w / 4 * angle_sin;  // нижняя линия 1

            col_corsx[4] = x - w / 4 * angle_cos - h / 2 * angle_sin;  // нижняя линия 2
            col_corsy[4] = y + h / 2 * angle_cos - w / 4 * angle_sin;  // нижняя линия 2

            col_corsx[5] = x - h / 2.5f * angle_sin;  // нижняя линия 3 (нижняя середина)
            col_corsy[5] = y + h / 2.5f * angle_cos;  // нижняя линия 3 (нижняя середина)

            col_corsx[6] = x + w / 2.5f * angle_cos;  // нос корабля
            col_corsy[6] = y + w / 2.5f * angle_sin;  // нос корабля

            col_corsx[7] = x - w / 2 * angle_cos;  // зад корабля
            col_corsy[7] = y - w / 2 * angle_sin;  // зад корабля

            col_corsx[8] = x - w / 2.5f * angle_cos + h / 2.5f * angle_sin;  // лев верх
            col_corsy[8] = y - h / 2.5f * angle_cos - w / 2.5f * angle_sin;  // лев верх

            col_corsx[9] = x + w / 2 * angle_cos + h / 2 * angle_sin;  // прав верх
            col_corsy[9] = y - h / 2 * angle_cos + w / 2 * angle_sin;  // прав верх

            col_corsx[10] = x + w / 2 * angle_cos - h / 2 * angle_sin;  // прав ниж
            col_corsy[10] = y + h / 2 * angle_cos + w / 2 * angle_sin;  // прав ниж

            col_corsx[11] = x - w / 2.5f * angle_cos - h / 2.5f * angle_sin;  // лев ниж
            col_corsy[11] = y + h / 2.5f * angle_cos - w / 2.5f * angle_sin;  // лев ниж
        }

        bool Shoot(ya::LaserPulse* lasers_array, unsigned short n_of_lasers) {
            if (n_of_lasers < 39) {
                float radians = angle * acos(-1) / 180;
                lasers_array[n_of_lasers].Setup(x + w / 2 * cosf(radians) - 10 * std::abs(sinf(radians)), y + w / 2 * sinf(radians) - 10 * std::abs(cosf(radians)),
                                                cosf(radians) * 0.5 + vel_x, sinf(radians) * 0.5 + vel_y);
                return true;
            }
            else { return false; }
        }

        void Rotate() {
            if (rotate_cw) {angle += ROTATION_SPEED;}
            if (rotate_acw)  {angle -= ROTATION_SPEED; }
      }

        void RotateWithMouse(sf::RenderWindow* win) {
            target_angle = atan2(sf::Mouse::getPosition(*win).y - y, sf::Mouse::getPosition(*win).x - x) * 180 / acos(-1);
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
        float getRadAlpha() {return angle * acos(-1) / 180; }
        float* getCollisionX() {return col_corsx; }
        float getCollisionX(unsigned short i) {return col_corsx[i]; }
        float* getCollisionY() {return col_corsy; }
        float getCollisionY(unsigned short i) {return col_corsy[i]; }
        bool isDestroyed() { return destroyed; }

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