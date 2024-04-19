#pragma once

#include "rectangle.hpp"
#include "triangle.hpp"
#include "line.hpp"
#include "circle.hpp"

namespace ya {
    class App {
        int window_width, window_height;
        wchar_t * window_title;
        sf::RenderWindow app_window;
        ya::Circle* circles;
        ya::Rectangle* rectangles;
        ya::Triangle* triangles;
//        sf::Vertex* lines[10];
        ya::Line* lines;
        unsigned short ng;
    public:
        App() {
            window_width = 500;
            window_height = 500;
            window_title = L"Window";
            app_window.create(sf::VideoMode(window_width, window_height), window_title);
        }

        App(int w, int h, wchar_t* string) {
            window_width = w;
            window_height = h;
            window_title = string;
            app_window.create(sf::VideoMode(window_width, window_height), window_title);
        }

        void setAllCircles() {
            int r, x, y;
            for (int i = 0; i < ng; i++) {
                r = rand() % 80 + 20;
                x = rand() % (window_width - r * 2) + r;
                y = rand() % (window_width - r * 2) + r;
                for (int j = 0; j < i; j++) {
                    float dist = powf(circles[j].getX() - x, 2) + powf(circles[j].getY() - y, 2);
                    if (dist <= powf(circles[j].getRadius() + r, 2)) {
                        r = rand() % 80 + 20;
                        x = rand() % (window_width - r * 2) + r;
                        y = rand() % (window_width - r * 2) + r;
                        j = -1; // в конце цикла for, j увеличится на 1  станет 0 (новый старт цикла)
                    }
                }
                circles[i].Setup(x, y, r, (rand() % 628) / 100.0f, i + 1);
            }
        }

        void setAllRects() {
            for (int i = 0; i < ng; i++) {
                rectangles[i].Setup(rand() % (window_width - window_width / 8),
                                    rand() % (window_height - window_height / 8),
                                    rand() % (window_width / 8) + 1,
                                    rand() % (window_height / 8) + 1);
            }
        }

        void setAllTriangles() {
            for (int i = 0; i < ng; i++) {
                triangles[i].Setup(rand() % (window_width - 40),
                                    rand() % (window_height - 40));
            }
        }

        void setAllLines() {
            for (int i = 0; i < ng; i++) {
//                lines[i][0].position = sf::Vector2f(rand() % (window_width - 40), rand() % (window_width - 40));
//                lines[i][1].position = sf::Vector2f(rand() % (window_width - 40), rand() % (window_width - 40));
                lines[i].Setup(rand() % (window_width - 20), rand() % (window_width - 20), rand() % (window_width - 20), rand() % (window_width - 20));
            }
        }

        void setApp(int n_objects=0) {
            if (n_objects > 10) {ng = 10;}
            else {ng = n_objects;}
            circles = new ya::Circle[ng];
            rectangles = new ya::Rectangle[ng];
            triangles = new ya::Triangle[ng];
            lines = new ya::Line[ng];
//            for (int i = 0; i < nl; i++) {
//                lines[i]->getLine() = new sf::Vertex[2];
//            }

            setAllTriangles();
            setAllCircles();
            setAllRects();
            setAllLines();
        }

        void ResetProgram() {
            setAllCircles();
            setAllRects();
            setAllTriangles();
            setAllLines();
        }

        void EventHandler() {
            sf::Event event;
            while (app_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) { app_window.close(); }
                if (event.type == sf::Event::MouseButtonPressed) { ResetProgram(); }
            }
        }

        void Render() {
            app_window.clear();
            for (int i = 0; i < ng; i++) {
                app_window.draw(circles[i].getShape());
                app_window.draw(rectangles[i].getShape());
                app_window.draw(triangles[i].getShape());
//                    app_window.draw(lines[i], 2, sf::Lines);
                app_window.draw(&lines[i].getLine(), 2, sf::Lines);
            }
            app_window.display();
        }

        void Update() {}

        void Run() {
            app_window.setFramerateLimit(30);
            while (app_window.isOpen()) {
                EventHandler();
                Update();
                Render();
            }
        }
    };
}