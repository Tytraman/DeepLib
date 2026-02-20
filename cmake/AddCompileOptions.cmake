function(deep_add_compile_options)
    set(prefix ARG)
    set(no_values "")
    set(single_values TARGET)
    set(multi_values "")

    cmake_parse_arguments(${prefix}
        "${no_values}" "${single_values}" "${multi_values}"
        ${ARGN}
    )

    if(NOT ARG_TARGET)
        message(FATAL_ERROR "deep_add_compile_options: TARGET argument is missing.")
    endif()

    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(CLANG_COMPILE_OPTIONS
            -Werror
            -Wall
            -Wextra
            -Wno-c++98-compat
            -Wno-c++98-compat-pedantic
            -Wno-c++20-compat
            -Wno-unsafe-buffer-usage
            -Wno-switch-enum
            -Wno-covered-switch-default
        )
    
        if(MSVC)
            foreach(FLAG ${CLANG_COMPILE_OPTIONS})
                target_compile_options(${ARG_TARGET} PRIVATE /clang:${FLAG})
            endforeach()
        else()
            target_compile_options(${ARG_TARGET} PRIVATE ${CLANG_COMPILE_OPTIONS})
        endif()
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(AddressSanitizer $<$<CONFIG:Debug>:/fsanitize=address>)

        target_compile_options(${ARG_TARGET} PRIVATE
            /WX     # Considère les warning comme des erreurs.
            /W4     # Niveau d'avertissement élevé.
            /utf-8  # Considère les chaînes de caractères en UTF-8 par défaut.
            ${AddressSanitizer}
        )

        target_link_options(${ARG_TARGET} PRIVATE ${AddressSanitizer})
    endif()

endfunction() #deep_add_compile_options