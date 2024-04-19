#pragma once


namespace ya {
    class Triangle {
        float pivot_x, pivot_y;
        sf::ConvexShape triangleShape;
    public:
        Triangle(){
            pivot_x = 0;
            pivot_y = 0;
        };

        Triangle(float x_cor, float y_cor) {
            Setup(x_cor, y_cor);
        }

        void Setup(float x_cor, float y_cor) {
            pivot_x = x_cor;
            pivot_y = y_cor;
            triangleShape.setPosition(pivot_x, pivot_y);
            triangleShape.setPointCount(3);
            triangleShape.setPoint(0, sf::Vector2f(0, 0));
            triangleShape.setPoint(1, sf::Vector2f(rand() % 20 + 20, 0));
            triangleShape.setPoint(2, sf::Vector2f(rand() % 10 + 10, rand() % 20 + 20));
            triangleShape.setFillColor(sf::Color(62, 185, 64, 255));
        }

        sf::ConvexShape getShape() {
            return triangleShape;
        }
    };
}