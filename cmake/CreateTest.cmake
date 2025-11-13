function(deep_create_test test_name)
    # La variable ARGN est pré-définie par CMake et contient la liste des tous les arguments qui n'ont pas de noms.
    # 'test_name' est un argument possédant un nom et n'est donc pas présent dans la liste ARGN.

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

    target_include_directories(${test_name}
        PRIVATE
            "${PNG_INCLUDE_DIRS}")

    target_link_libraries(${test_name}
        PRIVATE
            ${libs}
    )

    target_compile_options(${test_name}
        PRIVATE
            ${FSANITIZE_ADDR}
    )

    target_link_options(${test_name}
        PRIVATE
            ${FSANITIZE_ADDR}
    )

    add_test(NAME "Deep.${test_name}"
            COMMAND ${test_name})
endfunction() # deep_create_test