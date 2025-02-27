cmake_minimum_required(VERSION 3.15.7)

project(DeepLibProject
    VERSION 0.0.1
    LANGUAGES C CXX)

# Active la création et l'exécution de tests avec `ctest`.
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(DeepCore)

# Crée une cible nommée 'DeepLib'.
add_library(DeepLib SHARED
    deep.cpp)
add_library(Deep::Lib ALIAS DeepLib)

target_link_libraries(DeepLib PRIVATE
    Deep::Core)

# Défini la propriété VERSION de la cible 'DeepLib'.
set_target_properties(DeepLib PROPERTIES
    OUTPUT_NAME DeepLib
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PREFIX ""   # Retire le prefix du nom du fichier généré ('lib' sous Linux par exemple).
    # Indique que les symboles sont cachés par défaut, permettant une uniformisation entre les
    # différents compilateurs et un meilleur contrôle sur la sortie générée par le linker.
    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden
    # Indique que les fonctions 'inline' sont cachées par défaut, permettant de réduire la taille
    # du fichier généré lors de l'utilisation de templates en C++.
    VISIBILITY_INLINES_HIDDEN TRUE
)

# Crée une variable faisant référence au dossier 'include' pour faciliter l'intégration dans un projet.
set(DEEP_LIB_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

# Ajoute des options de compilation et de link selon le compilateur utilisé.
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Active l'outil de détection d'erreurs liées à la mémoire.
    set(FSANITIZE_ADDR $<$<CONFIG:Debug>:-fsanitize=address>)

    target_compile_options(DeepLib PRIVATE
        -Werror                                 # Considère les warning comme des erreurs.
        -Wall                                   # Active plusieurs warning.
        -Wextra                                 # Active encore plus de warning.
        ${FSANITIZE_ADDR}
    )

    target_link_options(DeepLib PRIVATE
        ${FSANITIZE_ADDR}
    )
endif()

# =====[ Liste des tests ]=====

# TODO: trouver un moyen de réduire le nombre de lignes à écrire pour ajouter un test

# Faire un test nécessite un exécutable avec une fonction `main`.
add_executable(TestSystem
  Test/test_system.cpp)
target_include_directories(TestSystem PRIVATE
    "${DEEP_CORE_INCLUDE_DIRS}"
    "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(TestSystem PRIVATE
    Deep::Core    # Comme le test utilise une fonction de cette librairie, il ne faut pas oublier de l'inclure.
    #Deep::Lib    # Le test n'utilise pas directement DeepLib, donc pas nécessaire de l'inclure.
)
target_compile_options(TestSystem PRIVATE
    ${FSANITIZE_ADDR}
)
target_link_options(TestSystem PRIVATE
    ${FSANITIZE_ADDR}
)

add_executable(TestGetCWD
    Test/test_get_cwd.cpp)
target_include_directories(TestGetCWD PRIVATE
    "${DEEP_CORE_INCLUDE_DIRS}"
    "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(TestGetCWD PRIVATE
    Deep::Core)
target_compile_options(TestGetCWD PRIVATE
    ${FSANITIZE_ADDR}
)
target_link_options(TestGetCWD PRIVATE
    ${FSANITIZE_ADDR}
)

add_executable(TestAllocMem
    Test/test_alloc_mem.cpp)
target_include_directories(TestAllocMem PRIVATE
    "${DEEP_CORE_INCLUDE_DIRS}"
    "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(TestAllocMem PRIVATE
    Deep::Core)
target_compile_options(TestAllocMem PRIVATE
    ${FSANITIZE_ADDR}
)
target_link_options(TestAllocMem PRIVATE
    ${FSANITIZE_ADDR}
)

# Crée un test nommé 'DeepCore.TestSystem' qui va exécuter la cible 'TestSystem'.
add_test(NAME DeepCore.TestSystem COMMAND TestSystem)
add_test(NAME DeepCore.TestGetCWD COMMAND TestGetCWD)
add_test(NAME DeepCore.TestAllocMem COMMAND TestAllocMem)


# Crée un lien symbolique vers 'compile_commands.json' généré dans le dossier de Build.
file(CREATE_LINK
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json   # Fichier pointé.
    ${CMAKE_CURRENT_LIST_DIR}/compile_commands.json     # Destination.
    COPY_ON_ERROR   # S'il n'est pas possible de créer de lien symbolique, fait une copie du fichier à la place.
    SYMBOLIC)


# =====[ Test de commandes CMake ]=====

# Ajoute une cible qui exécute une commande.
# ${CMAKE_COMMAND} pointe vers le chemin absolu de l'exécutable 'cmake'.
# -E indique que l'on veut exécuter une commande CMake qui sera cross-plateforme.
# Elle affichera le contenu de l'expression de générateur correspondant à la configuration utilisée.
add_custom_target(ShowConfig COMMAND ${CMAKE_COMMAND} -E echo "Current config: $<CONFIG>")

add_custom_target(ShowFSanitizeAddr COMMAND ${CMAKE_COMMAND} -E echo "FSANITIZE_ADDR: ${FSANITIZE_ADDR}")
