cmake_minimum_required(VERSION 3.15.7)

# Crée le projet auquel les cibles s'attacheront.
project(DeepLibProject
    VERSION 0.0.1
    LANGUAGES C CXX)

find_package(PNG REQUIRED)

# Active la création et l'exécution de tests avec `ctest`.
enable_testing()

set(CMAKE_CXX_STANDARD 17) # Utilise le standard C++17.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Génère un fichier 'compile_commands.json'.

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")

include(cmake/AddCompileOptions.cmake)

add_subdirectory("DeepCore")
add_subdirectory("DeepLib")

# Inclue la fonction 'deep_create_test'.
include(cmake/CreateTest.cmake)

deep_create_test(NAME GetCWD
    SOURCES test_get_cwd.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME AllocMem
    SOURCES test_alloc_mem.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME List
    SOURCES collection/test_list.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME RefCounted
    SOURCES test_ref_counted.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME OwnedPtr
    SOURCES test_owned_ptr.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME StringNative
    SOURCES string/test_string_native.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME String1
    SOURCES string/test_string1.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME String2
    SOURCES string/test_string2.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME ExecutablePath
    SOURCES string/test_executable_path.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME HashMap
    SOURCES collection/test_hash_map.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME MemoryStream
    SOURCES stream/test_memory_stream.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME FileStream
    SOURCES stream/test_file_stream.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME ImagePng
    SOURCES image/test_png.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME ImageApplyPalette
    SOURCES image/test_apply_palette.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME ImageApplyLuminance
    SOURCES image/test_apply_luminance.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME Math
    SOURCES maths/test_math.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME Vec2
    SOURCES maths/test_vec2.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME Vec3
    SOURCES maths/test_vec3.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME Mat4
    SOURCES maths/test_mat4.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME Thread
    SOURCES multithreading/test_thread.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME Bitmask
    SOURCES utils/test_bitmask.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME Bitset
    SOURCES utils/test_bitset.cpp
    LIBRARIES Deep::Lib)

deep_create_test(NAME Queue
    SOURCES collection/test_queue.cpp
    LIBRARIES Deep::Lib)

# Crée un lien symbolique vers 'compile_commands.json' généré dans le dossier de Build.
file(CREATE_LINK
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json   # Fichier pointé.
    ${CMAKE_CURRENT_LIST_DIR}/compile_commands.json     # Destination.
    COPY_ON_ERROR   # S'il n'est pas possible de créer de lien symbolique, fait une copie du fichier à la place.
    SYMBOLIC)

# --- Configuration du package ---

# Inclue le module permettant d'installer le projet sur la machine de l'utilisateur.
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(DeepInstallConfigDir "${CMAKE_INSTALL_LIBDIR}/cmake/DeepLib")
set(DeepLibConfigVersion "${CMAKE_CURRENT_BINARY_DIR}/DeepLibConfigVersion.cmake")
set(DeepLibConfig "${CMAKE_CURRENT_BINARY_DIR}/DeepLibConfig.cmake")

# Génère le fichier 'DeepLibConfigVersion.cmake'
write_basic_package_version_file("${DeepLibConfigVersion}"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

# Génère le fichier 'DeepLibConfig.cmake'
configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/DeepLibConfig.cmake.in"
    "${DeepLibConfig}"
    INSTALL_DESTINATION "${DeepInstallConfigDir}")

# --- Installation ---

install(TARGETS DeepCore
    EXPORT DeepLib-targets
    RUNTIME DESTINATION $<CONFIG>/${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION $<CONFIG>/${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION $<CONFIG>/${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/DeepCore/DeepCore"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp")

get_target_property(DeepCoreExport DeepCore DEEP_EXPORT_HEADER_FILE)

install(FILES "${DeepCoreExport}"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/DeepCore")

install(TARGETS DeepLib
    EXPORT DeepLib-targets
    RUNTIME DESTINATION $<CONFIG>/${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION $<CONFIG>/${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION $<CONFIG>/${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/DeepLib/DeepLib"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp")

get_target_property(DeepLibExport DeepLib DEEP_EXPORT_HEADER_FILE)

install(FILES "${DeepLibExport}"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/DeepLib")

install(EXPORT DeepLib-targets
    FILE DeepLibTargets.cmake
    NAMESPACE Deep::
    DESTINATION share/cmake/DeepLib
)

install(FILES
    "${DeepLibConfigVersion}"
    "${DeepLibConfig}"
    DESTINATION share/cmake/DeepLib
)

# --- Packaging ---

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(CPACK_PACKAGE_NAME DeepLib)
    set(CPACK_PACKAGE_VENDOR Tytraman)
    set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
    set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
    set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
    set(CPACK_VERBATIM_VARIABLES YES)

    if (WIN32)
        set(CPACK_GENERATOR ZIP)
    endif()

    include(CPack)
endif()