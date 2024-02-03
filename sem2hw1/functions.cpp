#include "functions.hpp"

namespace ya
{
    void GetTimeFormatted(char string[], char format[], size_t string_len) {
        time_t t = std::time(nullptr);
        std::strftime(string, string_len, format, std::localtime(&t));

        string[4] = '.';
        string[7] = '.';
        string[13] = ':';
        string[16] = ':';
        string[19] = '\n';
        string[20] = '\0';
    }

    unsigned short CountFileLines(const char& file_name) {
        std::string temp;
        std::ifstream in(&file_name);
        unsigned short lines_counter = 0;

        while (!in.eof()) {
            std::getline(in, temp);
            lines_counter++;
        }
        return lines_counter;
    }
}