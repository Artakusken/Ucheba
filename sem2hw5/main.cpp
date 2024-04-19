#include "circle.hpp"
#include "cycle.hpp"

int main() {
    ya::App krugis(800, 800, L"Кружочки");
    krugis.Setup(10);

    krugis.Run();

    return 0;
}