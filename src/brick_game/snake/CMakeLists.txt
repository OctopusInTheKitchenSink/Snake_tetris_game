cmake_minimum_required(VERSION 3.10)
project(MyGame)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# ВКЛЮЧИТЬ PIC ДО find_package!
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/Qt6/Qt6Config.cmake")

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)
find_library(RT_LIBRARY rt)

add_executable(My_game .    ../../gui/desktop/gamewidget.cpp
    ../../gui/desktop/gamewindow.cpp
    ../../gui/desktop/mainwindow.cpp
    ../../gui/desktop/snakegame.cpp
    ../../gui/desktop/statuswidget.cpp
    ../../gui/desktop/tetrisgame.cpp
    ../../gui/desktop/view.cpp
    ../../brick_game/snake/snake_controller.cpp ../../brick_game/tetris/common.c ../../brick_game/snake/snake_model.cpp ../../brick_game/tetris/backend.c)
target_include_directories(My_game PRIVATE
    ../../gui/desktop
    ../../brick_game/snake
    ../../brick_game/tetris
    ../../../src)
target_link_libraries(My_game Qt6::Widgets Qt6::Core Qt6::Gui rt)
