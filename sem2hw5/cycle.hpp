#pragma once

#include <SFML/Graphics.hpp>
#include "cmath"

namespace ya {
    class App {
        int window_width, window_height;
        int nc;
        wchar_t *window_title;
        sf::RenderWindow app_window;
        ya::Circle *circles;
    public:
        App() {
            window_width = 500;
            window_height = 500;
            window_title = L"Window";
            app_window.create(sf::VideoMode(window_width, window_height), window_title);
        }

        App(int width, int height, wchar_t *title) {
            window_width = width;
            window_height = height;
            window_title = title;
            app_window.create(sf::VideoMode(window_width, window_height), window_title);
        }

        void setAllCircles() {
            int r, x, y, v;
            float alpha;
            for (int i = 0; i < nc; i++) {
                r = rand() % 20 + 15;
                x = rand() % (window_width - 2 * r) + r;
                y = rand() % (window_height - 2 * r) + r;
                v = rand() % 50 + 10;
                alpha = (rand() % 628) / 100.0f;
                for (int j = 0; j < i; j++) {
                    float dist = pow(circles[j].getX() - x, 2) + pow(circles[j].getY() - y, 2);
                    if (dist <= powf(circles[j].getR() + r, 2)) {
                        r = rand() % 20 + 15;
                        x = rand() % (window_width - 2 * r) + r;
                        y = rand() % (window_height - 2 * r) + r;
                        j = -1; // в конце цикла for, j увеличится на 1  станет 0 (новый старт цикла)
                    }
                }
                circles[i].Setup(x, y, r, v, alpha);
            }
        }

        void Setup(int n) {
            if (n > 10) { nc = 10; }
            else { nc = n; }
            srand(time(0));

            circles = new ya::Circle[nc];
            setAllCircles();
        }

        void BorderCollision(Circle &c) {
            float x = c.getX();
            float y = c.getY();
            float r = c.getR();

            if (x + r >= window_width and c.getVelX() > 0) { c.InverseVelX(); }
            else if (x - r <= 0 and c.getVelX() < 0) { c.InverseVelX(); }
            if (y - r <= 0 and c.getVelY() < 0) { c.InverseVelY(); }
            else if (y + r >= window_height and c.getVelY() > 0) { c.InverseVelY(); }
        }


        void CirclesCollision(Circle &c1, Circle &c2, int i, int j) {
            float dist_x = c1.getX() - c2.getX();
            float dist_y = c1.getY() - c2.getY();
            float dist = dist_x * dist_x + dist_y * dist_y;
            if (dist <= pow(c1.getR() + c2.getR(), 2)) {
                float beta = acosf(dist_x / sqrtf(dist));
                if (dist_y > 0) { beta = -beta; }

                float v1x = c1.getVelX() * cosf(beta) - c1.getVelY() * sinf(beta);
                float v1y = c1.getVelX() * sinf(beta) + c1.getVelY() * cosf(beta);
                float v2x = c2.getVelX() * cosf(beta) - c2.getVelY() * sinf(beta);
                float v2y = c2.getVelX() * sinf(beta) + c2.getVelY() * cosf(beta);

                c1.setVelX(v2x * cosf(beta) + v1y * sinf(beta));
                c1.setVelY(-v2x * sinf(beta) + v1y * cosf(beta));
                c2.setVelX(v1x * cosf(beta) + v2y * sinf(beta));
                c2.setVelY(-v1x * sinf(beta) + v2y * cosf(beta));
            }
        }

        void ResetProgram() {
            setAllCircles();
        }

        void EventHandler() {
            sf::Event event;
            while (app_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) { app_window.close(); }
                if (event.type == sf::Event::MouseButtonPressed) { ResetProgram(); }
            }
        }

        void Update(float dt, float a) {
            for (int i = 0; i < nc; i++) {
                circles[i].Move(a * dt);
            }

            for (int i = 0; i < nc - 1; i++) {
                for (int j = i + 1; j < nc; j++) {
                    CirclesCollision(circles[i], circles[j], i, j);
                }
            }

            for (int i = 0; i < nc; i++) {
                BorderCollision(circles[i]);
            }
        }

        void Render() {
            app_window.clear();
            for (int i = 0; i < nc; i++) {
                app_window.draw(circles[i].getShape());
            }
            app_window.display();
        }

        void Run() {
            sf::Clock clock;
            float dt;

            while (app_window.isOpen()) {
                EventHandler();

                dt = clock.getElapsedTime().asSeconds();
                clock.restart();
                Update(dt, 5);

                Render();
            }
        }
    };
}