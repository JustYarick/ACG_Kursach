# Collision Simulation (OpenGL + ImGui)

## Технологии

- C++20
- OpenGL 3.3
- GLFW
- GLAD
- ImGui
- CMake
- vcpkg

## Установка зависимостей

Проект использует vcpkg.

Установить необходимые библиотеки:

vcpkg install glad glfw3 glm "imgui[glfw-binding,opengl3-binding]"

## Сборка проекта

Из корня проекта выполнить:

cmake -B build -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake

Пример:

cmake -B build -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake

Затем собрать:

cmake --build build

## Запуск

./build/ACG_Kursach
