#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "cmath"

namespace ya {
    class EnemyObjects {
    protected:
        float x, y; // coords
        float w, h; // bh size
        float vel_x, vel_y; // velocity
        float health;
        float scale;
        bool destroyed;

        sf::RectangleShape rectangleShape;
        sf::Texture objectTexture;
        sf::Sprite objectSprite;
    public:
        EnemyObjects() = default;

        EnemyObjects(float x_cor, float y_cor, float vx, float vy, float scale, float health_amount, char *image_path) {
            Setup(x_cor, y_cor, vx, vy, scale, health_amount, image_path);
        }

        void Setup(float x_cor, float y_cor, float vx, float vy, float scale_factor, float health_amount, char *image_path) {
            x = x_cor;
            y = y_cor;
            health = health_amount;
            vel_x = vx;
            vel_y = vy;
            scale = scale_factor;
            destroyed = false;
            w = 50;
            h = 50;

            if (!objectTexture.loadFromFile(image_path)) {
                rectangleShape.setPosition(x, y);
                rectangleShape.setSize(sf::Vector2(w, h));
                rectangleShape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
                std::cout << "Error while loading spaceship texture" << std::endl;
            }
            else {
                objectSprite.setTexture(objectTexture);
                objectTexture.setSmooth(true);
                objectSprite.setScale(scale, scale);
                w = objectSprite.getTextureRect().getSize().x * scale;
                h = objectSprite.getTextureRect().getSize().y * scale;
                std::cout << w << std::endl;

                objectSprite.setPosition(x, y);
                objectSprite.setOrigin(w*2.5, h*2.5);
            }
        }

        void Move(float dt) {
            x += vel_x * dt;
            y += vel_y * dt;
            rectangleShape.setPosition(x, y);
            objectSprite.setPosition(x, y);
        }

        void SuckInBH(float dist) {
            if (1000 / dist < scale - 0.1) {
                objectSprite.setScale(scale - 1000 / dist, scale - 1000 / dist);
                w = objectSprite.getTextureRect().getSize().x * objectSprite.getScale().x;
                h = objectSprite.getTextureRect().getSize().y * objectSprite.getScale().y;
//                objectSprite.setOrigin(w, h);
            }
        }

        void BehindBorders(int x_border, int y_border) {
            if ((x < 0 - w) or (x > x_border + w) or (y < 0 - h) or (y > y_border + h)) {
                destroyed = true;
            }
        }

        bool CollisionParticles(float other_x, float other_y, float other_w, float other_h) {
            float lx = x - w/2;
            float rx = x + w/2;
            float ty = y - h/2;
            float by = y + h/2;

            if ((other_x > lx and other_x < rx) and (other_y > ty and other_y < by)) {
                return true;
            }
            else if ((other_x + other_w > lx and other_x + other_w < rx) and (other_y > ty and other_y < by)) {
                return true;
            }
            else if ((other_x + other_w > lx and other_x + other_w < rx) and (other_y + other_h > ty and other_y + other_h < by)) {
                return true;
            }
            else if ((other_x > lx and other_x < rx) and (other_y + other_h > ty and other_y + other_h < by)) {
                return true;
            }
            return false;
        }

        bool CollisionShip(float other_x, float other_y, float other_w, float other_h, float angle_rad) {
            float other_lx = other_x - (other_w / 2) * cosf(angle_rad) + (other_h / 2) * sinf(angle_rad);
            float other_rx = other_x + (other_w / 2) * cosf(angle_rad) + (other_h / 2) * sinf(angle_rad);
            float other_ty = other_y - (other_h / 2) * cosf(angle_rad) - (other_w / 2) * sinf(angle_rad);
            float other_by = other_y + (other_h / 2) * cosf(angle_rad) - (other_w / 2) * sinf(angle_rad);

            float lx = x - w/2;
            float rx = x + w/2;
            float ty = y - h/2;
            float by = y + h/2;

            if ((other_lx > lx and other_lx < rx) and (other_ty > ty and other_ty < by)) {
                return true;
            }
            else if ((other_rx > lx and other_rx < rx) and (other_ty > ty and other_ty < by)) {
                return true;
            }
            else if ((other_rx > lx and other_rx < rx) and (other_by > ty and other_by < by)) {
                return true;
            }
            else if ((other_lx > lx and other_lx < rx) and (other_by + other_h > ty and other_by + other_h < by)) {
                return true;
            }
            return false;
        }

        void Destroy() {
            destroyed = true;
            x = y = -20;
            w = h = 0;
        }

        void TakeDamage(float damage) {
            health -= damage;
            if (health < 0) {
                Destroy();
            }
        }

        sf::RectangleShape getShape() {
            return rectangleShape;
        }

        sf::Sprite getSprite() {
            return objectSprite;
        }

        float getX() { return x; }
        float getY() { return y; }
        float getW() { return w; }
        float getH() { return h; }
        float isDestroyed() { return destroyed; }
        float getVelX() { return vel_x; }
        float getVelY() { return vel_y; }

        void changeVelX(float dvx) { vel_x += dvx; }
        void changeVelY(float dvy) { vel_y += dvy; }
    };

    class SpaceBase : public EnemyObjects { // убегает, ещё бьёт если корабль слишком близко (но не факт)
    public:
        SpaceBase() = default;
    };

    class Asteroid : public EnemyObjects { // просто чел
    public:
        Asteroid() = default;
    };

    class HostileAsteroid : public EnemyObjects { // догоняющий тебя негативчик
    public:
        HostileAsteroid() = default;
    };
}