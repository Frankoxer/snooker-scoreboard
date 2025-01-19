cmake_minimum_required(VERSION 3.29)
project(snooker_scoreboard)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(snooker_scoreboard main.cpp)
target_link_libraries(snooker_scoreboard
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

