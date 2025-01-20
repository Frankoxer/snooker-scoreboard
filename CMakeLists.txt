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

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Common
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

add_executable(snooker_scoreboard main.cpp
        Common/Match.h
        Common/Frame.h
        App/GameApp.cpp
        App/GameApp.h
        View/Window.cpp
        View/Window.h
        View/Window.ui
        ViewModel/MatchThread.cpp
        ViewModel/MatchThread.h
)
target_link_libraries(snooker_scoreboard
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

