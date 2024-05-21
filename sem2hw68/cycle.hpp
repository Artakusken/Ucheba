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
        float win_scale;
        bool run = true;

        const int more_space = 20;
        const int fps_lock = 120;
        const float particle_damage = 120;
        const float HostileAsteroid_health = 100;
        const float Asteroid_health = 100;
        const float SpaceBase_health = 1000;
        const float HostileAsteroid_scale = 0.2;
        const float Asteroid_scale = 0.2;
        const float SpaceBase_scale = 0.2;

        const char* Background_image_path = "..\\images\\system.jpg";
//        const char* Background_image_path = "..\\images\\system.jpg";
        const char* Font_path = "..\\images\\arial.ttf";
//        const char* Font_path = "images\\arial.ttf";
        const char* HostileAsteroid_image_path = "..\\images\\asteroid.png";
//        const char* HostileAsteroid_image_path = "images\\asteroid.png";
        const char* SpaceBase_image_path = "..\\images\\spacestation.png";
//        const char* HostileAsteroid_image_path = "images\\spacestation.png";
        const char* Asteroid_image_path = "..\\images\\asteroid.png";
//        const char* HostileAsteroid_image_path = "images\\asteroid.png";

        float laser_radius = 10;
        unsigned short n_of_lasers = 0;
        ya::LaserPulse *lasers;
        sf::CircleShape laserShape;

        int points;
        sf::Font font;
        sf::Text pointsText;

        unsigned short n_of_enemies;
        std::vector<ya::EnemyObjects*> enemies;

        sf::RenderWindow app_window;
        ya::Spaceship ship;
        ya::BlackHole black_hole;

        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
    public:
        App() = default;

        App(wchar_t *title, int resolution=0) {
            if (!resolution) {window_width=1920; window_height=1080; win_scale=1;}
            else {window_width=1280; window_height=720; win_scale = 0.66666666;}

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
                    enemies[i]->Setup(0, 0, -0.1*win_scale, 0, HostileAsteroid_scale * win_scale, HostileAsteroid_health, HostileAsteroid_image_path);
                }
                else if (i % 3 == 0) {
                    enemies.push_back(new SpaceBase);
                    enemies[i]->Setup(0, 0, -0.1*win_scale, 0, SpaceBase_scale * win_scale, SpaceBase_health, SpaceBase_image_path);
                }
                else {
                    enemies.push_back(new Asteroid);
                    enemies[i]->Setup(0, 0, -0.1*win_scale, 0, Asteroid_scale * win_scale, Asteroid_health, Asteroid_image_path);
                }
            }
            srand(time(nullptr));
            SpawnEnemyObjects();
        }

        void SpawnEnemyObjects() {
            for (unsigned short i=0; i < n_of_enemies; i++) {
                if (enemies[i]->isDestroyed())
                    enemies[i]->Spawn(window_width + rand() % 800, (rand() % (window_height - int(enemies[i]->getH()*2))) + enemies[i]->getH(), -rand() % 3 / 10.0f - 0.3, 0);
            }
        }

        void Setup() {
            ship.Setup(window_width / 2, window_height / 2, win_scale);
            black_hole.Setup(300, 400, win_scale);
            if (!backgroundTexture.loadFromFile(Background_image_path)) {
                std::cout << "Error while loading background texture" << std::endl;
            }
            else {
                backgroundSprite.setTexture(backgroundTexture);
                backgroundTexture.setSmooth(true);
                backgroundSprite.setScale(window_width / float(backgroundTexture.getSize().x),
                                          window_height / float(backgroundTexture.getSize().y));
                backgroundSprite.setPosition(0, 0);
            }

            if (!font.loadFromFile(Font_path)) {
                std::cout << "Error while loading arial.ttf" << std::endl;
            }
            else {
                points = 0;
                pointsText.setFont(font);
            }

            lasers = new ya::LaserPulse[40];
            laser_radius *= win_scale;
            laserShape.setRadius(laser_radius);

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
                    n_of_lasers += ship.Shoot(lasers, n_of_lasers, win_scale);
                }
            }
        }

        void Particles_Update(float dt) {
            for (unsigned short i=0; i < n_of_lasers; i++) {
                black_hole.BH_Force(lasers[i]);
                lasers[i].Move(dt);
            }

            int shift = 0;
            for (unsigned short i=0; i < n_of_lasers; i++) {
                if (lasers[i].BehindBorders(window_width, window_height)) {
                    shift++;
                    points -= 50;
                }
                else {
                    lasers[i - shift] = lasers[i];
                }
            }
            n_of_lasers -= shift;
        }

        void EnemiesUpdate(float dt) {
            SpawnEnemyObjects();
            for (unsigned short i=0; i < n_of_enemies; i++) {
                for (unsigned short j=0; j < n_of_lasers; j++) {
                    if (enemies[i]->CollisionParticles(lasers[j].getX(), lasers[j].getY(), 20*win_scale, 20*win_scale)) {
                        points += enemies[i]->TakeDamage(particle_damage);
                        lasers[j].Destroy();
                    }
                }
                for (unsigned short c = 0; c < 11; c++) {
                    if (enemies[i]->CollisionPoint(ship.getCollisionX(c), ship.getCollisionY(c))) {
                        ship.Destroy();
                    }
                }

                black_hole.BH_Force(*enemies[i]);
                enemies[i]->Move(dt);
                enemies[i]->SpecialMove(ship);
                enemies[i]->BehindBorders(window_width, window_height);
            }
        }

        void Update(float dt) {
            if (!ship.isDestroyed()) {
                ship.BorderCheck(window_width, window_height, more_space);
                ship.accelerate();
                ship.decelerate();
                ship.Move(dt);
                ship.RotateWithMouse(app_window);
                ship.CalculateCollision();
            }
            Particles_Update(dt);
            EnemiesUpdate(dt);
            black_hole.BH_Force(ship);
            black_hole.ReachedTarget(window_width, window_height);
            black_hole.Move(dt);
            pointsText.setString(std::to_string(points));
        }

        void Particles_Render() {
            for (unsigned short i=0; i < n_of_lasers; i++) {
                laserShape.setFillColor(sf::Color(255, 2, 2, 255));

                laserShape.setPosition(lasers[i].getX(), lasers[i].getY());
                laserShape.setScale(lasers[i].getScale(), lasers[i].getScale());
                app_window.draw(laserShape);
                if (DEBUG) {
                    float l = laser_radius * 2;

                    laserShape.setRadius(2);
                    laserShape.setFillColor(sf::Color(2, 255, 2, 255));

                    laserShape.setPosition(lasers[i].getX(), lasers[i].getY());
                    app_window.draw(laserShape);

                    laserShape.setPosition(lasers[i].getX() + l, lasers[i].getY());
                    app_window.draw(laserShape);

                    laserShape.setPosition(lasers[i].getX() + l, lasers[i].getY() + l);
                    app_window.draw(laserShape);

                    laserShape.setPosition(lasers[i].getX(), lasers[i].getY() + l);
                    app_window.draw(laserShape);
                    laserShape.setRadius(laser_radius);
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

                        laserShape.setRadius(laser_radius);
                    }
                }
            }
        }

        void Render() {
            app_window.clear();
            app_window.draw(backgroundSprite);
            app_window.draw(black_hole.getSprite());
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

                    laserShape.setRadius(laser_radius);
                }
                if (DEBUG) {
                    laserShape.setRadius(2);
                    laserShape.setFillColor(sf::Color(2, 2, 255, 255));

                    laserShape.setPosition(ship.getX(), ship.getY());
                    app_window.draw(laserShape);


                    laserShape.setPosition(ship.getX() - std::abs((ship.getW() / 2) * cosf(ship.getRadAlpha()))
                                                         - std::abs((ship.getH() / 2) * sinf(ship.getRadAlpha())), ship.getY() - std::abs((ship.getH() / 2) * cosf(ship.getRadAlpha()))
                                                                                                                                 - std::abs((ship.getW() / 2) * sinf(ship.getRadAlpha())));
                    app_window.draw(laserShape);

                    laserShape.setPosition(ship.getX() + std::abs((ship.getW() / 2) * cosf(ship.getRadAlpha()))
                                           + std::abs((ship.getH() / 2) * sinf(ship.getRadAlpha())), ship.getY() - std::abs((ship.getH() / 2) * cosf(ship.getRadAlpha()))
                                                                                                                       - std::abs((ship.getW() / 2) * sinf(ship.getRadAlpha())));
                    app_window.draw(laserShape);

                    laserShape.setPosition(ship.getX() + std::abs((ship.getW() / 2) * cosf(ship.getRadAlpha()))
                                           + std::abs((ship.getH() / 2) * sinf(ship.getRadAlpha())), ship.getY() + std::abs((ship.getH() / 2) * cosf(ship.getRadAlpha()))
                                                                          + std::abs((ship.getW() / 2) * sinf(ship.getRadAlpha())));
                    app_window.draw(laserShape);

                    laserShape.setPosition(ship.getX() - std::abs((ship.getW() / 2) * cosf(ship.getRadAlpha()))
                                           - std::abs((ship.getH() / 2) * sinf(ship.getRadAlpha())), ship.getY() + std::abs((ship.getH() / 2) * cosf(ship.getRadAlpha()))
                                                                          + std::abs((ship.getW() / 2) * sinf(ship.getRadAlpha())));
                    app_window.draw(laserShape);

                    laserShape.setRadius(laser_radius);
                }
                if (DEBUG) {
                    float* aga = ship.getCollisionX();
                    float* ugu= ship.getCollisionY();

                    laserShape.setRadius(2);
                    laserShape.setFillColor(sf::Color(255, 2, 2, 255));

                    laserShape.setPosition(ship.getX(), ship.getY());
                    app_window.draw(laserShape);
                    laserShape.setPosition(aga[0],ugu[0]);
                    app_window.draw(laserShape);
                    laserShape.setPosition(aga[1],ugu[1]);
                    app_window.draw(laserShape);
                    laserShape.setPosition(aga[2],ugu[2]);
                    app_window.draw(laserShape);
                    laserShape.setPosition(aga[3],ugu[3]);
                    app_window.draw(laserShape);
                    laserShape.setPosition(aga[4],ugu[4]);
                    app_window.draw(laserShape);
                    laserShape.setPosition(aga[5],ugu[5]);
                    app_window.draw(laserShape);
                    laserShape.setPosition(aga[6],ugu[6]);
                    app_window.draw(laserShape);
                    laserShape.setPosition(aga[7],ugu[7]);
                    app_window.draw(laserShape);
                    laserShape.setPosition(aga[8],ugu[8]);
                    app_window.draw(laserShape);
                    laserShape.setPosition(aga[9],ugu[9]);
                    app_window.draw(laserShape);
                    laserShape.setPosition(aga[10],ugu[10]);
                    app_window.draw(laserShape);
                    laserShape.setPosition(aga[11],ugu[11]);
                    app_window.draw(laserShape);

                    laserShape.setRadius(laser_radius);
                }
            }
            EnemiesRender();
            Particles_Render();
            app_window.draw(pointsText);
            app_window.display();
        }

        void Run() {
            sf::Clock clock;
            app_window.setFramerateLimit(fps_lock);
            while (app_window.isOpen() and run and !ship.isDestroyed()) {
                EventHandler();

                clock.restart();
                Update(600/fps_lock);

                Render();
            }
            std::cout << "GAME OVER\n";
            std::cout << "POINTS: " << points;
        }
    };
}