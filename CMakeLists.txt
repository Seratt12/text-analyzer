cmake_minimum_required(VERSION 3.23)

project(text-analyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Drogon CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_subdirectory(src/core)
add_subdirectory(src/app)

# --- Тесты ---
enable_testing()
add_subdirectory(tests)