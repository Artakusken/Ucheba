#include "functions.hpp"

int main() {
    std::ofstream out("dates.txt", std::ios::app);

    char result[21];
    char classic_time_format[18] = "%Y %m %d %H %M %S";

    ya::GetTimeFormatted(result, classic_time_format, 21);
    unsigned short lines_counter = ya::CountFileLines(*"dates.txt");

    out << lines_counter << ") "  << result;
}
