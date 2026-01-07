cmake_minimum_required(VERSION 3.15.7)

add_library(DeepCore
    SHARED
        "${CMAKE_CURRENT_LIST_DIR}/DeepCore/context.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/DeepCore/filesystem.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/DeepCore/memory.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/DeepCore/event.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/DeepCore/thread.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/DeepCore/term.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/DeepCore/string/unicode.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/DeepCore/string/utf8.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/DeepCore/window.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/DeepCore/vkeys.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/DeepCore/time.cpp"
)
add_library(Deep::Core ALIAS DeepCore)

set(DeepCoreExport "${CMAKE_CURRENT_BINARY_DIR}/export/DeepCore/deep_core_export.h")

include(GenerateExportHeader)
generate_export_header(DeepCore
    EXPORT_FILE_NAME "${DeepCoreExport}"
    EXPORT_MACRO_NAME DEEP_CORE_API)

set_target_properties(DeepCore PROPERTIES
    DEEP_EXPORT_HEADER_FILE "${DeepCoreExport}")

set_target_properties(DeepCore PROPERTIES
    OUTPUT_NAME DeepCore
    EXPORT_NAME Core
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PREFIX ""
    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN TRUE)

# Ajoute les fichiers sources selon le système cible.
if(UNIX)
    target_sources(DeepCore
        PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/DeepCore/unix/filesystem.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/DeepCore/unix/error.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/DeepCore/unix/memory.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/DeepCore/unix/event.cpp"
    )
elseif(WIN32)
    target_sources(DeepCore
        PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/DeepCore/windows/context.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/DeepCore/windows/filesystem.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/DeepCore/windows/error.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/DeepCore/windows/memory.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/DeepCore/windows/event.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/DeepCore/windows/thread.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/DeepCore/windows/term.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/DeepCore/windows/window.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/DeepCore/windows/time.cpp"
    )
endif()



target_include_directories(DeepCore
    PUBLIC
        # 1. Pour la compilation locale (BUILD_INTERFACE)
        # On inclut la source ET le dossier de build (pour deep_core_export.h généré)
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/export>

        # 2. Pour l'installation (INSTALL_INTERFACE)
        # On indique aux utilisateurs d'aller chercher dans le dossier "include" de l'installation
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

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


