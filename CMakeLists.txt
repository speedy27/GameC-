cmake_minimum_required(VERSION 3.10)
project(PokemonCpp)

set(CMAKE_CXX_STANDARD 14)

# Trouver les packages SFML
find_package(SFML 2.5 COMPONENTS graphics audio system window REQUIRED)

# Définir les fichiers source
set(SOURCES
    src/main.cpp
    src/Pokemon.cpp
    src/Battle.cpp
    src/Game.cpp
    src/SFMLGame.cpp
)

# Créer l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Inclure les répertoires d'en-têtes
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Lier les bibliothèques SFML
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-audio
    sfml-system
    sfml-window
)

# Copier les ressources dans le répertoire de build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)