#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

namespace ya
{
    void GetTimeFormatted(char string[], char format[], size_t string_len);

    unsigned short CountFileLines(const char& file_name);
}
