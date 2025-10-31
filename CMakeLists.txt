cmake_minimum_required(VERSION 3.15.7)

# Crée le projet auquel les cibles s'attacheront.
project(DeepLibProject
    VERSION 0.0.1
    LANGUAGES C CXX)

# Active la création et l'exécution de tests avec `ctest`.
enable_testing()

set(CMAKE_CXX_STANDARD 17) # Utilise le standard C++17.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Génère un fichier 'compile_commands.json'.

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")

add_subdirectory(DeepCore)
add_subdirectory(DeepLib)

# Inclue la fonction 'deep_create_test'.
include(cmake/CreateTest.cmake)

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

deep_create_test(HashMap LINK_DEEP_CORE LINK_DEEP_LIB
    SOURCES test_hash_map.cpp)

deep_create_test(MemoryStream LINK_DEEP_CORE LINK_DEEP_LIB
    SOURCES stream/test_memory_stream.cpp)

# Crée un lien symbolique vers 'compile_commands.json' généré dans le dossier de Build.
file(CREATE_LINK
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json   # Fichier pointé.
    ${CMAKE_CURRENT_LIST_DIR}/compile_commands.json     # Destination.
    COPY_ON_ERROR   # S'il n'est pas possible de créer de lien symbolique, fait une copie du fichier à la place.
    SYMBOLIC)