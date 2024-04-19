cmake_minimum_required(VERSION 3.26)
project(Ucheba)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


add_definitions(-DSFML_STATIC)

include_directories("../liba/SFML/include/")
link_directories("../liba/SFML/lib/")

add_executable(Ucheba main.cpp
		circle.hpp
		cycle.hpp
)
											
target_link_libraries(Ucheba sfml-graphics-s-d
						  sfml-window-s-d
						  sfml-system-s-d
						  opengl32
						  freetype
						  winmm
						  gdi32
						  sfml-audio-s-d
						  openal32
						  flac
						  vorbisenc
						  vorbisfile
						  vorbis
						  ogg)