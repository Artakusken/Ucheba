#include <SFML/Graphics.hpp>
#include "cycle.hpp"

int main() {
    int win_width = 800;
    int win_heigth = 800;
    int NumberOfObjects = 10;

    ya::App figures(win_width, win_heigth, L"Супрематизм");
    figures.setApp(NumberOfObjects);
    figures.Run();

    return 0;
}