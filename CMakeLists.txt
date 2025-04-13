cmake_minimum_required(VERSION 3.10)
project(PokemonCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Inclure SFML
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

# Inclure répertoires include
include_directories(include)

# Fichiers sources
file(GLOB SOURCES "src/*.cpp")

# Exécutable
add_executable(PokemonCpp ${SOURCES})

# Lier SFML
target_link_libraries(PokemonCpp sfml-graphics sfml-window sfml-system sfml-audio)
