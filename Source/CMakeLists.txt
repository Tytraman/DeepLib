cmake_minimum_required(VERSION 3.15.7)

project(DeepLibProject
    VERSION 0.0.1
    LANGUAGES C CXX)

# Active la création et l'exécution de tests avec `ctest`.
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(DeepCore)

# Crée une cible nommée 'DeepLib'.
add_library(DeepLib SHARED
    context.cpp
    lib.cpp
    memory/memory_manager.cpp
    memory/ref_counted.cpp
)
add_library(Deep::Lib ALIAS DeepLib)

target_link_libraries(DeepLib PRIVATE
    Deep::Core)

get_target_property(deep_core_bin_dir DeepCore BINARY_DIR)

target_include_directories(DeepLib PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${deep_core_bin_dir}")

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

message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")

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
set_source_files_properties(lib.cpp PROPERTIES
    COMPILE_DEFINITIONS "${defs}")

include(GenerateExportHeader)
generate_export_header(DeepLib
    EXPORT_FILE_NAME deep_lib_export.h
    EXPORT_MACRO_NAME DEEP_LIB_API)

# =====[ Liste des tests ]=====

function(deep_create_test test_name)
    # La variable ARGN est pré-définie par CMake et contient la liste des tous les arguments qui n'ont pas de noms.
    # target_name est un argument possédant un nom : 'target_name', il n'est donc pas présent dans la liste ARGN.

    set(prefix ARG)
    set(no_values LINK_DEEP_CORE LINK_DEEP_LIB)
    set(single_values SINGLE)
    set(multi_values SOURCES)

    set(src)
    set(libs)

    cmake_parse_arguments(
        ${prefix}
        "${no_values}" "${single_values}" "${multi_values}"
        ${ARGN}
    )

    string(PREPEND test_name "Test")

    # Ajoute automatiquement le dossier "Test" dans le chemin du fichier source,
    # permettant d'éviter de l'écrire à chaque appel de 'deep_create_test'.
    foreach(arg IN LISTS ${prefix}_SOURCES)
        string(PREPEND arg "Test/")
        list(APPEND src ${arg})
    endforeach()

    # Link le test avec les différentes librairies si spécifié.
    if(${prefix}_LINK_DEEP_CORE)
        list(APPEND libs Deep::Core)
    endif()

    if(${prefix}_LINK_DEEP_LIB)
        list(APPEND libs Deep::Lib)
    endif()

    # Crée un exécutable pour le test.
    add_executable(${test_name} ${src})

    target_include_directories(${test_name} PRIVATE
        "${DEEP_CORE_INCLUDE_DIRS}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_BINARY_DIR}")

    target_link_libraries(${test_name} PRIVATE
        ${libs})

    target_compile_options(${test_name} PRIVATE
        ${FSANITIZE_ADDR})

    target_link_options(${test_name} PRIVATE
        ${FSANITIZE_ADDR})

    add_test(NAME "Deep.${test_name}"
            COMMAND ${test_name})
endfunction() # deep_create_test

deep_create_test(GetCWD LINK_DEEP_CORE LINK_DEEP_LIB
    SOURCES test_get_cwd.cpp)

deep_create_test(AllocMem LINK_DEEP_CORE LINK_DEEP_LIB
    SOURCES test_alloc_mem.cpp)

deep_create_test(List LINK_DEEP_CORE LINK_DEEP_LIB
    SOURCES test_list.cpp)

deep_create_test(RefCounted LINK_DEEP_CORE LINK_DEEP_LIB
    SOURCES test_ref_counted.cpp)

deep_create_test(OwnedPtr LINK_DEEP_CORE LINK_DEEP_LIB
    SOURCES test_owned_ptr.cpp)

deep_create_test(StringNative LINK_DEEP_CORE LINK_DEEP_LIB
    SOURCES test_string_native.cpp)

deep_create_test(String1 LINK_DEEP_CORE LINK_DEEP_LIB
    SOURCES test_string1.cpp)

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

add_custom_target(ShowProjectVersion COMMAND ${CMAKE_COMMAND} -E echo "DEEP_LIB_VERSION: ${DeepLibProject_VERSION}")
