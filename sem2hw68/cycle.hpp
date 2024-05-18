#pragma once

#include <SFML/Graphics.hpp>
#include "cmath"
#include "iostream"
#include "enemys.hpp"
#include "black_hole.hpp"
#include "particles.hpp"

const extern bool DEBUG = true;

namespace ya {
    class App {
        int window_width, window_height;
        wchar_t *window_title;
        float scale;
        bool run = true;

        const int more_space = 20;
        const int fps_lock = 120;

        unsigned short n_of_lasers = 0;
        ya::LaserPulse *lasers;
        sf::CircleShape laserShape;

        unsigned short n_of_enemies;
        std::vector<ya::EnemyObjects*> enemies;

        sf::RenderWindow app_window;
        ya::Spaceship ship;
        ya::BlackHole bh;

        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
    public:
        App() {
            window_width = 500;
            window_height = 500;
            window_title = L"Window";
            scale = 1;
            app_window.create(sf::VideoMode(window_width, window_height), window_title, sf::Style::Fullscreen);
        }

        App(wchar_t *title, int resolution=0) {
            if (!resolution) {window_width=1920; window_height=1080; scale=1;}
            else {window_width=1280; window_height=720; scale = 0.66666666;}
            window_title = title;
            if (!resolution) {
                app_window.create(sf::VideoMode(window_width, window_height), window_title, sf::Style::None);
            }
            else {
                app_window.create(sf::VideoMode(window_width, window_height), window_title, sf::Style::Default);
            }
        }

        ~App() {
            delete[] lasers;
            for (unsigned short i=0; i < n_of_enemies; i++) {
                delete enemies[i];
            }
        }

        void SetEnemyObjects() {
            for (unsigned short i=0; i < n_of_enemies; i++) {
                if (i % 2 == 0) {
                    enemies.push_back(new HostileAsteroid);
                    enemies[i]->Setup(800, 400, 0, 0, 0.2, 100, "..\\images\\asteroid.png");
                }
                else if (i % 3 == 0) {
                    enemies.push_back(new SpaceBase);
                    enemies[i]->Setup(1500, 600, 0, 0, 0.2, 100, "..\\images\\spacestation.png");
                }
                else {
                    enemies.push_back(new Asteroid);
                    enemies[i]->Setup(100, 100, 0, 0, 0.2, 100, "..\\images\\asteroid.png");
                }
            }
        }

        void Setup() {
            ship.Setup(window_width / 2, window_height / 2, scale);
            bh.Setup(300, 400, scale);
            if (!backgroundTexture.loadFromFile("..\\images\\system.jpg")) {
                std::cout << "Error while loading background texture" << std::endl;
            }
            else {
                backgroundSprite.setTexture(backgroundTexture);
                backgroundTexture.setSmooth(true);
                backgroundSprite.setScale(window_width / float(backgroundTexture.getSize().x),
                                          window_height / float(backgroundTexture.getSize().y));
                backgroundSprite.setPosition(0, 0);
            }

            lasers = new ya::LaserPulse[40];
            laserShape.setRadius(10);

//            enemies = new ya::EnemyObjects[4]*;
            n_of_enemies = 4;
            SetEnemyObjects();
        }

        void EventHandler() {
            sf::Event event;
            while (app_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) { app_window.close(); }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == 0) {ship.setVelMX(true);}  // A
                    if (event.key.code == 3) {ship.setVelPX(true);}  // D
                    if (event.key.code == 18) {ship.setVelPY(true);}  // S
                    if (event.key.code == 22) {ship.setVelMY(true);}  // W
                    if (event.key.code == 38) {ship.setFaster(true);}  // Shift
                    if (event.key.code == 57) {ship.setStop(true);}  // Space
                    if (event.key.code == 4) {ship.StartRotation(true);}  // E
                    if (event.key.code == 16) {ship.StartRotation(false);}  // Q
                }
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == 0) {ship.setVelMX(false);}
                    if (event.key.code == 3) {ship.setVelPX(false);}
                    if (event.key.code == 18) {ship.setVelPY(false);}
                    if (event.key.code == 22) {ship.setVelMY(false);}
                    if (event.key.code == 38) {ship.setFaster(false);}
                    if (event.key.code == 57) {ship.setStop(false);}
                    if (event.key.code == 4) {ship.EndRotation(true);}
                    if (event.key.code == 16) {ship.EndRotation(false);}
                    if (event.key.code == 36) {run = false;}
                }
                if (event.type == sf::Event::MouseButtonPressed and !ship.isDestroyed()) {
                    n_of_lasers += ship.Shoot(lasers, n_of_lasers);
                }
            }
        }

        void Particles_Update(float dt) {
            for (unsigned short i=0; i < n_of_lasers; i++) {
                bh.BH_Force(lasers[i]);
                lasers[i].Move(dt);
            }

            int shift = 0;
            for (unsigned short i=0; i < n_of_lasers; i++) {
                if (lasers[i].BehindBorders(window_width, window_height)) {
                    shift++;
                }
                else {
                    lasers[i - shift] = lasers[i];
                }
            }
            n_of_lasers -= shift;

//            for (unsigned short i=0; i < n_of_lasers; i++) {
//                std::cout << lasers[i].getX() << " " << lasers[i].getY() << "; ";
//            }
//            std::cout << " * " << n_of_lasers << " * \n";
        }

        void EnemiesUpdate(float dt) {
            for (unsigned short i=0; i < n_of_enemies; i++) {
                for (unsigned short j=0; j < n_of_lasers; j++) {
                    if (enemies[i]->CollisionParticles(lasers[j].getX(), lasers[j].getY(), 20, 20)) {
                        enemies[i]->TakeDamage(120);
                        std::cout << "1\n";
                        lasers[j].Destroy();
                    }
                }
                if (enemies[i]->CollisionShip(ship.getX(), ship.getY(), ship.getW(), ship.getH(), ship.getAlpha() * acos(-1) / 180)) {
                    ship.Destroy();
                    std::cout << "2\n";
                }
                bh.BH_Force(*enemies[i]);
                enemies[i]->Move(dt);
            }
        }

        void Update(float dt) {
            if (!ship.isDestroyed()) {
                ship.BorderCheck(window_width, window_height, more_space);
                ship.accelerate();
                ship.decelerate();
                ship.Move(dt);
                ship.RotateWithMouse(&app_window);
            }
            Particles_Update(dt);
            EnemiesUpdate(dt);
            bh.BH_Force(ship);
        }

        void Particles_Render() {
            for (unsigned short i=0; i < n_of_lasers; i++) {
                laserShape.setFillColor(sf::Color(255, 2, 2, 255));

                laserShape.setPosition(lasers[i].getX(), lasers[i].getY());
                laserShape.setScale(lasers[i].getScale(), lasers[i].getScale());
//                laserShape.setOrigin(10, 10);
                app_window.draw(laserShape);
                if (DEBUG) {
                    laserShape.setRadius(2);
                    laserShape.setFillColor(sf::Color(2, 255, 2, 255));

                    laserShape.setPosition(lasers[i].getX(), lasers[i].getY());
                    app_window.draw(laserShape);

                    laserShape.setPosition(lasers[i].getX() + 20, lasers[i].getY());
                    app_window.draw(laserShape);

                    laserShape.setPosition(lasers[i].getX() + 20, lasers[i].getY() + 20);
                    app_window.draw(laserShape);

                    laserShape.setPosition(lasers[i].getX(), lasers[i].getY() + 20);
                    app_window.draw(laserShape);
                    laserShape.setRadius(10);
                }
            }
        }

        void EnemiesRender() {
            for (unsigned short i=0; i < n_of_enemies; i++) {
                if (!enemies[i]->isDestroyed()) {
                    app_window.draw(enemies[i]->getSprite());
                    if (DEBUG) {
                        laserShape.setRadius(2);
                        laserShape.setFillColor(sf::Color(2, 255, 2, 255));

                        laserShape.setPosition(enemies[i]->getX(), enemies[i]->getY());
                        app_window.draw(laserShape);

                        laserShape.setPosition(enemies[i]->getX() - enemies[i]->getW() / 2,
                                               enemies[i]->getY() - enemies[i]->getH() / 2);
                        app_window.draw(laserShape);

                        laserShape.setPosition(enemies[i]->getX() + enemies[i]->getW() / 2,
                                               enemies[i]->getY() - enemies[i]->getH() / 2);
                        app_window.draw(laserShape);

                        laserShape.setPosition(enemies[i]->getX() + enemies[i]->getW() / 2,
                                               enemies[i]->getY() + enemies[i]->getH() / 2);
                        app_window.draw(laserShape);

                        laserShape.setPosition(enemies[i]->getX() - enemies[i]->getW() / 2,
                                               enemies[i]->getY() + enemies[i]->getH() / 2);
                        app_window.draw(laserShape);

                        laserShape.setRadius(10);
                    }
                }
            }
        }

        void Render() {
            app_window.clear();
            app_window.draw(backgroundSprite);
            app_window.draw(bh.getSprite());
            if (!ship.isDestroyed()) {
                app_window.draw(ship.getSprite());
                if (DEBUG) {
                    laserShape.setRadius(2);
                    laserShape.setFillColor(sf::Color(2, 255, 2, 255));

                    laserShape.setPosition(ship.getX() - ship.getW() / 2, ship.getY() - ship.getH() / 2);
                    app_window.draw(laserShape);

                    laserShape.setPosition(ship.getX() + ship.getW() / 2, ship.getY() - ship.getH() / 2);
                    app_window.draw(laserShape);

                    laserShape.setPosition(ship.getX() + ship.getW() / 2, ship.getY() + ship.getH() / 2);
                    app_window.draw(laserShape);

                    laserShape.setPosition(ship.getX() - ship.getW() / 2, ship.getY() + ship.getH() / 2);
                    app_window.draw(laserShape);

                    laserShape.setRadius(10);
                }
                if (DEBUG) {
                    laserShape.setRadius(2);
                    laserShape.setFillColor(sf::Color(2, 2, 255, 255));

                    laserShape.setPosition(ship.getX(), ship.getY());
                    app_window.draw(laserShape);


                    laserShape.setPosition(ship.getX() - std::abs((ship.getW() / 2) * cosf(ship.getAlpha() * acos(-1) / 180))
                                                         - std::abs((ship.getH() / 2) * sinf(ship.getAlpha() * acos(-1) / 180)), ship.getY() - std::abs((ship.getH() / 2) * cosf(ship.getAlpha() * acos(-1) / 180))
                                                                                                                                 - std::abs((ship.getW() / 2) * sinf(ship.getAlpha() * acos(-1) / 180)));
                    app_window.draw(laserShape);

                    laserShape.setPosition(ship.getX() + std::abs((ship.getW() / 2) * cosf(ship.getAlpha() * acos(-1) / 180))
                                           + std::abs((ship.getH() / 2) * sinf(ship.getAlpha() * acos(-1) / 180)), ship.getY() - std::abs((ship.getH() / 2) * cosf(ship.getAlpha() * acos(-1) / 180))
                                                                                                                       - std::abs((ship.getW() / 2) * sinf(ship.getAlpha() * acos(-1) / 180)));
                    app_window.draw(laserShape);

                    laserShape.setPosition(ship.getX() + std::abs((ship.getW() / 2) * cosf(ship.getAlpha() * acos(-1) / 180))
                                           + std::abs((ship.getH() / 2) * sinf(ship.getAlpha() * acos(-1) / 180)), ship.getY() + std::abs((ship.getH() / 2) * cosf(ship.getAlpha() * acos(-1) / 180))
                                                                          + std::abs((ship.getW() / 2) * sinf(ship.getAlpha() * acos(-1) / 180)));
                    app_window.draw(laserShape);

                    laserShape.setPosition(ship.getX() - std::abs((ship.getW() / 2) * cosf(ship.getAlpha() * acos(-1) / 180))
                                           - std::abs((ship.getH() / 2) * sinf(ship.getAlpha() * acos(-1) / 180)), ship.getY() + std::abs((ship.getH() / 2) * cosf(ship.getAlpha() * acos(-1) / 180))
                                                                          + std::abs((ship.getW() / 2) * sinf(ship.getAlpha() * acos(-1) / 180)));
                    app_window.draw(laserShape);

                    laserShape.setRadius(10);
                }

                if (DEBUG) {
                    laserShape.setRadius(2);
                    laserShape.setFillColor(sf::Color(255, 2, 2, 255));

                    laserShape.setPosition(ship.getX(), ship.getY());
                    app_window.draw(laserShape);


                    laserShape.setPosition(ship.getX() - (ship.getW() / 2) * cosf(ship.getAlpha() * acos(-1) / 180)
                                            + (ship.getH() / 2) * sinf(ship.getAlpha() * acos(-1) / 180), ship.getY() - (ship.getH() / 2) * cosf(ship.getAlpha() * acos(-1) / 180)
                              - (ship.getW() / 2) * sinf(ship.getAlpha() * acos(-1) / 180));
                    app_window.draw(laserShape);

                    laserShape.setPosition(ship.getX() + (ship.getW() / 2) * cosf(ship.getAlpha() * acos(-1) / 180)
                                           + (ship.getH() / 2) * sinf(ship.getAlpha() * acos(-1) / 180), ship.getY() - (ship.getH() / 2) * cosf(ship.getAlpha() * acos(-1) / 180)
                                                                                                                       + (ship.getW() / 2) * sinf(ship.getAlpha() * acos(-1) / 180));
                    app_window.draw(laserShape);

                    laserShape.setPosition(ship.getX() +(ship.getW() / 2) * cosf(ship.getAlpha() * acos(-1) / 180)
                                           - (ship.getH() / 2) * sinf(ship.getAlpha() * acos(-1) / 180), ship.getY() + (ship.getH() / 2) * cosf(ship.getAlpha() * acos(-1) / 180)
                                                                                                                   + (ship.getW() / 2) * sinf(ship.getAlpha() * acos(-1) / 180));
                    app_window.draw(laserShape);

                    laserShape.setPosition(ship.getX() - (ship.getW() / 2) * cosf(ship.getAlpha() * acos(-1) / 180)
                                           - (ship.getH() / 2) * sinf(ship.getAlpha() * acos(-1) / 180), ship.getY() + (ship.getH() / 2) * cosf(ship.getAlpha() * acos(-1) / 180)
                                                                                                                   - (ship.getW() / 2) * sinf(ship.getAlpha() * acos(-1) / 180));
                    app_window.draw(laserShape);

                    laserShape.setRadius(10);
                }
            }
            EnemiesRender();
            Particles_Render();
            app_window.display();
        }

        void Run() {
            sf::Clock clock;
            app_window.setFramerateLimit(fps_lock);
            while (app_window.isOpen() and run) {
                EventHandler();

                clock.restart();
                Update(5);

                Render();
            }
        }
    };
}