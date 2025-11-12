cmake_minimum_required(VERSION 3.10)
project(Proyecto1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always -g")

# Buscar todos los archivos .cpp en subcarpetas (relativo al directorio del CMakeLists.txt)
file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/view/*.cpp"
    "${CMAKE_SOURCE_DIR}/controller/*.cpp"
    "${CMAKE_SOURCE_DIR}/model/*.cpp"
)

# Incluir directorios de headers
include_directories(${CMAKE_SOURCE_DIR})

# Crear ejecutable
add_executable(Proyecto1 ${SOURCES})

# Establecer el directorio de salida del ejecutable
set_target_properties(Proyecto1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copiar carpeta data/ automáticamente después de compilar
add_custom_command(TARGET Proyecto1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/data"
    "${CMAKE_BINARY_DIR}/bin/data"
    COMMENT "Copiando carpeta data/ al directorio de salida..."
)
