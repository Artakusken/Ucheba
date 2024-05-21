#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "cmath"
#include "spaceship.hpp"

namespace ya {
    class EnemyObjects {
    protected:
        float x, y; // coords
        float w, h; // bh size
        float vel_x, vel_y; // velocity
        float health;
        float cur_health;
        float scale;
        bool destroyed;

        const float max_vel = 0.4;
        sf::Texture objectTexture;
        sf::Sprite objectSprite;
    public:
        EnemyObjects() = default;

        EnemyObjects(float x_cor, float y_cor, float vx, float vy, float scale, float health_amount, char *image_path) {
            Setup(x_cor, y_cor, vx, vy, scale, health_amount, image_path);
        }

        virtual ~EnemyObjects() {}

        void Setup(float x_cor, float y_cor, float vx, float vy, float scale_factor, float health_amount, const char *image_path) {
            x = x_cor;
            y = y_cor;
            health = health_amount;
            cur_health = health_amount;
            vel_x = vx;
            vel_y = vy;
            scale = scale_factor;
            destroyed = true;
            w = 50;
            h = 50;

            if (!objectTexture.loadFromFile(image_path)) {
                std::cout << "Error while loading spaceship texture" << std::endl;
            }
            else {
                objectSprite.setTexture(objectTexture);
                objectTexture.setSmooth(true);
                objectSprite.setScale(scale, scale);
                w = objectSprite.getTextureRect().getSize().x * scale;
                h = objectSprite.getTextureRect().getSize().y * scale;

                objectSprite.setPosition(x, y);
                objectSprite.setOrigin((w/(2*objectSprite.getScale().x)), (h/(2*objectSprite.getScale().y)));
                w *= 0.9;
                h *= 0.9;
            }
        }

        void Spawn(float x_cor, float y_cor, float vx, float vy) {
            x = x_cor;
            y = y_cor;
            vel_x = vx;
            vel_y = vy;
            destroyed = false;
            cur_health = health;
        }

        void Move(float dt) {
            x += vel_x * dt;
            y += vel_y * dt;
            objectSprite.setPosition(x, y);
        }

        void SuckInBH(float dist) {
            if (1000 / dist < scale - 0.1) {
                objectSprite.setScale(scale - 1000 / dist, scale - 1000 / dist);
                w = objectSprite.getTextureRect().getSize().x * objectSprite.getScale().x;
                h = objectSprite.getTextureRect().getSize().y * objectSprite.getScale().y;
                w *= 0.9;
                h *= 0.9;
            }
        }

        void BehindBorders(int x_border, int y_border) {
            if ((x < 0 - w and vel_x < 0) or (x > x_border + w and vel_x > 0)
                or (y < 0 - h and vel_y < 0) or (y > y_border + h and vel_y > 0)) {
                Destroy();
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

        bool CollisionPoint(float other_x, float other_y) {
            float lx = x - w/2;
            float rx = x + w/2;
            float ty = y - h/2;
            float by = y + h/2;

            if ((other_x > lx and other_x < rx) and (other_y > ty and other_y < by)) {
                return true;
            }
            return false;
        }

        void Destroy() {
            destroyed = true;
            x = y = -20;
            vel_x = vel_y = 0;
            objectSprite.setScale(scale, scale);
            w = objectSprite.getTextureRect().getSize().x * scale * 0.9;
            h = objectSprite.getTextureRect().getSize().y * scale * 0.9;
        }

        int TakeDamage(float damage) {  // возвращает очки за уничтожение объекта
            cur_health -= damage;
            if (cur_health < 0) {
                Destroy();
                return health;
            }
            return 0;
        }

        virtual void SpecialMove(ya::Spaceship& ship) = 0;

        sf::Sprite getSprite() {
            return objectSprite;
        }

        float getX() { return x; }
        float getY() { return y; }
        float getW() { return w; }
        float getH() { return h; }
        float getVelX() { return vel_x; }
        float getVelY() { return vel_y; }
        bool isDestroyed() { return destroyed; }

        void changeVelX(float dvx) { vel_x += dvx; }
        void changeVelY(float dvy) { vel_y += dvy; }
    };

    class SpaceBase : public EnemyObjects { // убегает, если корабль слишком близко
    public:
        SpaceBase() = default;

        void SpecialMove(ya::Spaceship& ship) override {
            float dist = powf(x - ship.getX(), 2) + powf(y - ship.getY(), 2);
            if (ship.getY() > y and vel_y > -max_vel) { changeVelY((1 / dist) * -300); }
            else if (vel_y < max_vel) { changeVelY((1 / dist) * 300); }
        }
    };

    class Asteroid : public EnemyObjects { // просто чел
    public:
        Asteroid() = default;

        void SpecialMove(ya::Spaceship& ship) override {

        }
    };

    class HostileAsteroid : public EnemyObjects { // догоняющий тебя негативчик
    public:
        HostileAsteroid() = default;

        void SpecialMove(ya::Spaceship& ship) override {
            if (!ship.isDestroyed()) {
                float dist = powf(x - ship.getX(), 2) + powf(y - ship.getY(), 2);
                if (ship.getY() > y and vel_y < max_vel) { changeVelY((1 / dist) * 300); }
                else if (vel_y > -max_vel) { changeVelY((1 / dist) * -300); }
                if (ship.getX() > x and vel_x < max_vel) { changeVelX((1 / dist) * 300); }
                else if (vel_x > -max_vel) { changeVelX((1 / dist) * -300); }
            }
        }
    };
}