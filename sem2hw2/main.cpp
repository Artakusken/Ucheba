#include "iostream"
#include "cmath"

struct Point {
    float x = 0;
    float y = 0;
};

class Ellipse {
    float semi_major_axis, semi_minor_axis = 0;
    float x_offset, y_offset = 0;
    Point focus_1 = {0, 0};
    Point focus_2 = {0, 0};
    Point center = {0, 0};
    float eccentricity = 0;

public:
    Ellipse(float a, float b, float h, float k) {
        x_offset = h;
        y_offset = k;
        center.x = x_offset;
        center.y = y_offset;

        if (a < 0) {
            a = -a;
            std::cout << "Constructor WARNING! Semi major axis cannot be negative. Value changed to positive\n";
        }
        if (b < 0) {
            b = -a;
            std::cout << "Constructor WARNING! Semi minor axis cannot be negative. Value changed to positive\n";
        }

        if (a > b) {
            semi_major_axis = a;
            semi_minor_axis = b;
            focus_1.x = std::sqrt(a*a - b*b) + x_offset;
            focus_1.y = y_offset;
            focus_2.x = -std::sqrt(a*a - b*b) + x_offset;
            focus_2.y = y_offset;
        }
        else {
            semi_major_axis = b;
            semi_minor_axis = a;
            focus_1.x = x_offset;
            focus_1.y = std::sqrt(b*b - a*a) + y_offset;
            focus_2.x = x_offset;
            focus_2.y = -std::sqrt(b*b - a*a) + y_offset;
        }

        eccentricity = std::sqrt((1 - powf(semi_minor_axis / semi_major_axis, 2.0)));
    }

    void InfoPrint() {
        std::cout << "-------------------------------------------------------\n";
        std::cout << "area: " << getArea() << "\n";
        std::cout << "f1(x, y): " << focus_1.x << " " << focus_1.y << "\n";
        std::cout << "f2(x, y): " << focus_2.x << " " << focus_2.y << "\n";
        std::cout << "center(x, y): " << center.x << " " << center.y << "\n";
        std::cout << "eccentricity: " << eccentricity << "\n";
        std::cout << "perimeter: " << getPerimeter() << "\n";
        std::cout << "-------------------------------------------------------\n";
    }

    double getEccentricity() {
        return eccentricity;
    }

    double getArea() {
        return acos(-1) * semi_major_axis * semi_minor_axis;
    }

    double getPerimeter() {
        // ↓ приближённая формула, про формулы периметра эллипса - https://www.mathsisfun.com/geometry/ellipse-perimeter.html
        return acos(-1) * (3*(semi_major_axis+semi_minor_axis) - std::sqrt(
                (3*semi_major_axis+semi_minor_axis)*(semi_major_axis+3*semi_minor_axis)
                ));
//        return acos(-1) * sqrtf( // менее точная формула
//                2*(semi_major_axis*semi_major_axis + semi_minor_axis*semi_minor_axis)
//        );
    }

    Point getCenter() {
        return center;
    }

    Point* getFocalPoints(Point FociPoints[2]) {
        FociPoints[0] = focus_1;
        FociPoints[1] = focus_2;
        return FociPoints;
    }

//    ~Ellipse() { // У меня нет контейнеров и массивов, поэтому деструктор сам освободит память
//        std::cout << "Destr" << "\n";
//    }
};


int main() {
    // a - большая полуось (если a < b, то оси поменяются: b станет большой полуосью, а - малой)
    // b - малая полуось
    // h - отклонение от центра с/к по Ох
    // k - отклонение от центра с/к по Оу
    Ellipse elipsoid(30, 21, 0, 0);
    elipsoid.InfoPrint();
    Ellipse nothing(0, 0, 0, 0);
    nothing.InfoPrint();
    Ellipse negative(-2, 6, -3, -1);
    negative.InfoPrint();
}