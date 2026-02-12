cmake_minimum_required(VERSION 3.21)
project(ACG_Kursach)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES
    ./src/*.cpp
)

add_executable(ACG_Kursach ${SOURCES})

target_include_directories(ACG_Kursach PRIVATE src)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

target_link_libraries(ACG_Kursach
    glad::glad
    glfw
    glm::glm
    imgui::imgui
)

