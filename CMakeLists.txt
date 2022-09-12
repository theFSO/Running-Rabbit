cmake_minimum_required(VERSION 3.20)
project(3gc3_final)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)



add_executable(3gc3_final
        main.cpp
        src/object.cpp
        src/object.h
        src/lighting.cpp
        src/lighting.h src/Player.cpp src/Player.h src/Obstacle.cpp src/Obstacle.h src/Lane.cpp src/Lane.h src/utli.cpp src/utli.h)

target_link_libraries(3gc3_final -lfreeglut -lglu32 -lopengl32)
