cmake_minimum_required(VERSION 3.26)
project(Ucheba)

set(CMAKE_CXX_STANDARD 17)

include_directories("/")

add_executable(Ucheba main.cpp
        functions.cpp
        functions.hpp)

# У меня в CLion, working directory находится в папке с билдом (cmake-build-debug), поэтому файлы с данными создаются/читаются сразу там
# Строка снизу У МЕНЯ ничего не меняет в работе программы, но оставлю на всякий случай
# Файлы.jpg - скрин структуры файлов
file(COPY "cmake-build-debug/dates.txt" DESTINATION "/")