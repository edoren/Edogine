set(EXAMPLES
    scenes
)

include_directories(${PROJECT_SOURCE_DIR}/include)

if(${OS} STREQUAL "Windows")
    # Add the include directories for external libraries for search
    include_directories(${PROJECT_SOURCE_DIR}/extlibs/include)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${PROJECT_SOURCE_DIR}/extlibs/include)

    # Add the libraries of the external libraries for search
    if(${COMPILER} STREQUAL "MSVC")
        if(${COMPILER_ARCH} EQUAL 32)
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${PROJECT_SOURCE_DIR}/extlibs/libs-msvc12/x86)
        elseif(${COMPILER_ARCH} EQUAL 64)
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${PROJECT_SOURCE_DIR}/extlibs/libs-msvc12/x64)
        endif()
    endif()
endif()

find_library(EDOGINE_LIB
    NAMES Edogine Edogine-d
    PATHS ${PROJECT_BINARY_DIR}/lib
)
mark_as_advanced(EDOGINE_LIB)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

foreach(EXAMPLE ${EXAMPLES})

    add_executable(example_${EXAMPLE} ${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE}/main.cpp)
    target_link_libraries(example_${EXAMPLE} ${EDOGINE_LIB})

    set_target_properties(example_${EXAMPLE} PROPERTIES
        OUTPUT_NAME ${EXAMPLE}
        FOLDER "Examples"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/examples/${EXAMPLE}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/examples/${EXAMPLE}
    )

    if(SDL2_FOUND)
        include_directories(${SDL2_INCLUDE_DIR})
        target_link_libraries(example_${EXAMPLE} ${SDL2_LIBRARIES})
    endif()

    if(SDL2_IMAGE_FOUND)
        include_directories(${SDL2_IMAGE_INCLUDE_DIR})
        target_link_libraries(example_${EXAMPLE} ${SDL2_IMAGE_LIBRARY})
    endif()

endforeach()