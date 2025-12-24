cmake_minimum_required(VERSION 3.15.7)

# Crée une cible nommée 'DeepLib' qui se lie au projet précédemment créé.
# Dans ce cas là, 'DeepLibProject'.
add_library(DeepLib SHARED
    DeepLib/context.cpp
    DeepLib/object.cpp
    DeepLib/lib.cpp
    DeepLib/maths/math.cpp
    DeepLib/maths/color.cpp
    DeepLib/string/string.cpp
    DeepLib/filesystem/filesystem.cpp
    DeepLib/multithreading/event.cpp
    DeepLib/multithreading/thread.cpp
    DeepLib/stream/memory_stream.cpp
    DeepLib/stream/file_stream.cpp
    DeepLib/stream/text_writer.cpp
    DeepLib/stream/stream_writer.cpp
    DeepLib/image/png.cpp
    DeepLib/image/image.cpp
    DeepLib/window/window.cpp
    DeepLib/window/keyboard.cpp
)
add_library(Deep::Lib ALIAS DeepLib)

set(DeepLibExport "${CMAKE_CURRENT_BINARY_DIR}/export/DeepLib/deep_lib_export.h")

include(GenerateExportHeader)
generate_export_header(DeepLib
    EXPORT_FILE_NAME ${DeepLibExport}
    EXPORT_MACRO_NAME DEEP_LIB_API)

set_target_properties(DeepLib PROPERTIES
    DEEP_EXPORT_HEADER_FILE "${DeepLibExport}")

target_link_libraries(DeepLib
    PUBLIC
        Deep::Core
        PNG::PNG)

set_target_properties(DeepLib PROPERTIES
    OUTPUT_NAME DeepLib
    EXPORT_NAME Lib
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PREFIX ""   # Retire le prefix du nom du fichier généré ('lib' sous Linux par exemple).
    # Indique que les symboles sont cachés par défaut, permettant une uniformisation entre les
    # différents compilateurs et un meilleur contrôle sur la sortie générée par le linker.
    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden
    # Indique que les fonctions 'inline' sont cachées par défaut, permettant de réduire la taille
    # du fichier généré lors de l'utilisation de templates en C++.
    VISIBILITY_INLINES_HIDDEN TRUE)

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
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Active l'outil de détection d'erreurs liées à la mémoire.
    set(FSANITIZE_ADDR $<$<CONFIG:Debug>:/fsanitize=address>)

    target_compile_options(DeepLib PRIVATE
        /WX     # Considère les warning comme des erreurs.
        /W4     # Niveau d'avertissement élevé.
        ${FSANITIZE_ADDR}
    )

    target_link_options(DeepLib PRIVATE
        ${FSANITIZE_ADDR}
    )
endif()

# Récupère la liste des définitions du fichier 'deep.cpp'.
get_source_file_property(defs lib.cpp COMPILE_DEFINITIONS)
# Ajoute à la liste de définitions, les valeurs de la version du projet.
list(APPEND defs "DEEP_LIB_VERSION=\"${DeepLibProject_VERSION}\"")
# Met à jour les définitions pour le fichier 'deep.cpp'.
set_source_files_properties(DeepLib/lib.cpp PROPERTIES
    COMPILE_DEFINITIONS "${defs}")

target_include_directories(DeepLib
    PUBLIC
        # 1. Compilation locale : Source + Dossier de build (pour l'export généré)
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/export>

        # 2. Installation : Indique aux clients de regarder dans le dossier 'include'
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# =====[ Test de commandes CMake ]=====

# Ajoute une cible qui exécute une commande.
# ${CMAKE_COMMAND} pointe vers le chemin absolu de l'exécutable 'cmake'.
# -E indique que l'on veut exécuter une commande CMake qui sera cross-plateforme.
# Elle affichera le contenu de l'expression de générateur correspondant à la configuration utilisée.
add_custom_target(ShowConfig COMMAND ${CMAKE_COMMAND} -E echo "Current config: $<CONFIG>")

add_custom_target(ShowFSanitizeAddr COMMAND ${CMAKE_COMMAND} -E echo "FSANITIZE_ADDR: ${FSANITIZE_ADDR}")

add_custom_target(ShowProjectVersion COMMAND ${CMAKE_COMMAND} -E echo "DEEP_LIB_VERSION: ${DeepLibProject_VERSION}")
