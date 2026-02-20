function(deep_create_test)
    # La variable ARGN est pré-définie par CMake et contient la liste des tous les arguments qui n'ont pas de noms.
    # 'test_name' est un argument possédant un nom et n'est donc pas présent dans la liste ARGN.

    set(prefix ARG)
    set(no_values "")
    set(single_values NAME)
    set(multi_values SOURCES LIBRARIES)

    set(src)

    cmake_parse_arguments(${prefix}
        "${no_values}" "${single_values}" "${multi_values}"
        ${ARGN}
    )

    # Ajoute automatiquement le dossier "Test" dans le chemin du fichier source,
    # permettant d'éviter de l'écrire à chaque appel de 'deep_create_test'.
    foreach(arg IN LISTS ${prefix}_SOURCES)
        string(PREPEND arg "Test/")
        list(APPEND src ${arg})
    endforeach()

    set(test_target "DeepLib.${ARG_NAME}")

    # Crée un exécutable pour le test.
    add_executable("${test_target}" ${src})

    target_link_libraries("${test_target}"
        PRIVATE
            ${ARG_LIBRARIES}
    )

    deep_add_compile_options(TARGET "${test_target}")

    add_test(NAME "${test_target}"
            COMMAND "${test_target}")
endfunction() # deep_create_test