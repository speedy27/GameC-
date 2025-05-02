
cmake_minimum_required(VERSION 3.10)
project(SimulateurPokemon)

set(CMAKE_CXX_STANDARD 11)
include_directories(${PROJECT_SOURCE_DIR})

file(GLOB SRC *.cpp)
add_executable(simulateur_pokemon ${SRC})

file(GLOB CSV *.csv)
foreach(f ${CSV})
    configure_file(${f} ${f} COPYONLY)
endforeach()
