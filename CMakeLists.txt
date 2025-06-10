cmake_minimum_required(VERSION 3.10)

# Tên dự án
project(RPG_Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RPG_Game
        main.cpp
        src/Game.cpp
        src/Player.cpp
        src/Monster.cpp
        src/Weapon.cpp
)

target_include_directories(RPG_Game PUBLIC ${PROJECT_SOURCE_DIR}/include)