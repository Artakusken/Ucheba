#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "cmath"

namespace ya {
    class BlackHole {
        float x, y; // coords
        float w, h; // bh size
        const float gravity_force = 250;

        sf::RectangleShape rectangleShape;
        sf::Texture bhTexture;
        sf::Sprite bhSprite;
    public:
        BlackHole() {
            x = y = 200;
        };

        BlackHole(float x_cor, float y_cor, float scale) {
            Setup(x_cor, y_cor, scale);
        }

        void Setup(float x_cor, float y_cor, float scale) {
            x = x_cor;
            y = y_cor;
            w = 50;
            h = 50;

            if (!bhTexture.loadFromFile("..\\images\\black_hole.png")) {
                rectangleShape.setPosition(x, y);
                rectangleShape.setSize(sf::Vector2(w, h));
                rectangleShape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
                std::cout << "Error while loading spaceship texture" << std::endl;
            }
            else {
                bhSprite.setTexture(bhTexture);
                bhTexture.setSmooth(true);
                bhSprite.setScale(0.2f * scale, 0.2f * scale);
                w = bhSprite.getTextureRect().getSize().x * 0.5f;
                h = bhSprite.getTextureRect().getSize().y * 0.5f;

                bhSprite.setPosition(x, y);
                bhSprite.setOrigin(w, h);
            }
        }

        void BH_Force(ya::Spaceship& ship) {
            float dist = powf(x - ship.getX(), 2) + powf(y - ship.getY(), 2);
            if (dist < 200000 and dist > 2000) {
                if (x > ship.getX()) { ship.changeVelX(10000 / (dist * dist) * gravity_force); }
                else { ship.changeVelX(-10000 / (dist * dist) * gravity_force); }
                if (y > ship.getY()) { ship.changeVelY(10000 / (dist * dist) * gravity_force); }
                else { ship.changeVelY(-10000 / (dist * dist) * gravity_force); }
                ship.SuckInBH(dist);
            }
            if (dist < 2000 and !ship.isDestroyed()) {
                ship.Destroy();
                ship.changeVelX(-ship.getVelX());
                ship.changeVelY(-ship.getVelY());
            }
        }

        void BH_Force(ya::LaserPulse& laser) {
            float dist = powf(x - laser.getX(), 2) + powf(y - laser.getY(), 2);
            if (dist < 200000 and dist > 2000) {
                if (x > laser.getX()) { laser.changeVelX(10000 / (dist * dist) * gravity_force); }
                else { laser.changeVelX(-10000 / (dist * dist) * gravity_force); }
                if (y > laser.getY()) { laser.changeVelY(10000 / (dist * dist) * gravity_force); }
                else { laser.changeVelY(-10000 / (dist * dist) * gravity_force); }
                laser.SuckInBH(dist);
            }
            if (dist < 2000) {
                laser.Destroy();
            }
        }

        void BH_Force(ya::EnemyObjects& enemy) {
            float dist = powf(x - enemy.getX(), 2) + powf(y - enemy.getY(), 2);
            if (dist < 200000 and dist > 2000) {
                if (x > enemy.getX()) { enemy.changeVelX(10000 / (dist * dist) * gravity_force); }
                else { enemy.changeVelX(-10000 / (dist * dist) * gravity_force); }
                if (y > enemy.getY()) { enemy.changeVelY(10000 / (dist * dist) * gravity_force); }
                else { enemy.changeVelY(-10000 / (dist * dist) * gravity_force); }
                enemy.SuckInBH(dist);
            }
            if (dist < 2000 and !enemy.isDestroyed()) {
                enemy.Destroy();
            }
        }

        sf::RectangleShape getShape() {
            return rectangleShape;
        }

        sf::Sprite getSprite() {
            return bhSprite;
        }

        float getX() { return x; }
        float getY() { return y; }
        float getGravity() { return gravity_force; }
    };
}