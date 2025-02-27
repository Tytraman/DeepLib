cmake_minimum_required(VERSION 3.15.7)

add_library(DeepCore SHARED
    core.cpp
    filesystem.cpp
    memory.cpp
)
add_library(Deep::Core ALIAS DeepCore)

target_include_directories(DeepCore PUBLIC
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
endif()


