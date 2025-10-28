cmake_minimum_required(VERSION 3.15.7)

add_library(DeepCore SHARED
    context.cpp
    filesystem.cpp
    memory.cpp
    string/unicode.cpp)
add_library(Deep::Core ALIAS DeepCore)

target_include_directories(DeepCore PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}")

set_target_properties(DeepCore PROPERTIES
    OUTPUT_NAME DeepCore
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PREFIX ""
    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN TRUE
)

set(DEEP_CORE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}" PARENT_SCOPE)

# Ajoute les fichiers sources selon le système cible.
if(UNIX)
    target_sources(DeepCore PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/unix/filesystem.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/unix/error.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/unix/memory.cpp"
    )
elseif(WIN32)
    target_sources(DeepCore PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/windows/context.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/windows/filesystem.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/windows/error.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/windows/memory.cpp"
        
    )
endif()

include(GenerateExportHeader)
generate_export_header(DeepCore
    EXPORT_FILE_NAME deep_core_export.h
    EXPORT_MACRO_NAME DEEP_CORE_API)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(FSANITIZE_ADDR $<$<CONFIG:Debug>:-fsanitize=address>)
    
    target_compile_options(DeepCore PRIVATE
        -Werror            
        -Wall
        -Wextra            
        ${FSANITIZE_ADDR}
    )

    target_link_options(DeepCore PRIVATE
        ${FSANITIZE_ADDR}
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Active l'outil de détection d'erreurs liées à la mémoire.
    set(FSANITIZE_ADDR $<$<CONFIG:Debug>:/fsanitize=address>)

    target_compile_options(DeepCore PRIVATE
        /WX     # Considère les warning comme des erreurs.
        /W4     # Niveau d'avertissement élevé.
        ${FSANITIZE_ADDR}
    )

    target_link_options(DeepCore PRIVATE
        ${FSANITIZE_ADDR}
    )
endif()


