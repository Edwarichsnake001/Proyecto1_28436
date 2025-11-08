cmake_minimum_required(VERSION 3.10)
project(Proyecto1)

set(CMAKE_CXX_STANDARD 17)

# Buscar todos los archivos .cpp en subcarpetas
file(GLOB_RECURSE SOURCES
    "view/*.cpp"
    "controller/*.cpp"
    "model/*.cpp"
)

add_executable(Proyecto1 ${SOURCES})
