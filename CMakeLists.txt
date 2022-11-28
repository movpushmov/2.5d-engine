cmake_minimum_required(VERSION 3.23)
project(game)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(game main.cpp src/render.cpp src/entities/GameObject.cpp src/entities/GameObject.h src/entities/Person.cpp src/entities/Person.h src/utils/math.cpp src/utils/math.h src/render/Ray.cpp src/render/Ray.h src/entities/World.cpp src/entities/World.h src/render.h)

target_link_libraries(game sfml-graphics sfml-audio)