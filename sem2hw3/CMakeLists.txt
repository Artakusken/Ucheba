cmake_minimum_required(VERSION 3.26)
project(Ucheba)

set(CMAKE_CXX_STANDARD 17)

#add_executable(Ucheba main.cpp
#        pseudo_string.cpp
#        pseudo_string.hpp)

set(PROJECT_HEADERS
        pseudo_string.hpp
)
set(PROJECT_SOURCES
        main.cpp
        pseudo_string.cpp
)

add_executable(Ucheba ${PROJECT_SOURCES} ${PROJECT_HEADERS})