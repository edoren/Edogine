# Set the library source and header directories
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

# Library name
set(EDOGINE_TARGET "EDOGINE")

include_directories(${INCLUDE_DIR})

set(CORE_SRC
    ${SRC_DIR}/Edogine/Core/GameEngine.cpp
    ${SRC_DIR}/Edogine/Core/GameScene.cpp
    ${SRC_DIR}/Edogine/Core/SceneManager.cpp
    ${INCLUDE_DIR}/Edogine/Core/SceneManager.inl
    ${SRC_DIR}/Edogine/Core/ResourceManager.cpp
)

set(CORE_HEADERS
    ${INCLUDE_DIR}/Edogine/Core/GameEngine.hpp
    ${INCLUDE_DIR}/Edogine/Core/GameScene.hpp
    ${INCLUDE_DIR}/Edogine/Core/SceneManager.hpp
    ${INCLUDE_DIR}/Edogine/Core/ResourceManager.hpp
    ${INCLUDE_DIR}/Edogine/Core/Context.hpp
)

set(GRAPHICS_SRC
    ${SRC_DIR}/Edogine/Graphics/Sprite.cpp
    ${SRC_DIR}/Edogine/Graphics/Animator.cpp
)

set(GRAPHICS_HEADERS
    ${INCLUDE_DIR}/Edogine/Graphics/Sprite.hpp
    ${INCLUDE_DIR}/Edogine/Graphics/Animator.hpp
)

set(SYSTEM_SRC
    ${SRC_DIR}/Edogine/System/Time.cpp
    ${SRC_DIR}/Edogine/System/Clock.cpp
    ${INCLUDE_DIR}/Edogine/System/Vector2.inl
)

set(SYSTEM_HEADERS
    ${INCLUDE_DIR}/Edogine/System/Time.hpp
    ${INCLUDE_DIR}/Edogine/System/Clock.hpp
    ${INCLUDE_DIR}/Edogine/System/Vector2.hpp
)

set(OTHER_HEADERS
    ${INCLUDE_DIR}/Edogine/Config.hpp
    ${INCLUDE_DIR}/Edogine/Edogine.hpp
)

set(EDOGINE_SOURCES ${CORE_SRC} ${GRAPHICS_SRC} ${SYSTEM_SRC})
set(EDOGINE_HEADERS ${OTHER_HEADERS} ${CORE_HEADERS} ${GRAPHICS_HEADERS} ${SYSTEM_HEADERS})

# Build the library
if(EDOGINE_SHARED_LIB)
    add_library(${EDOGINE_TARGET} SHARED ${EDOGINE_SOURCES} ${EDOGINE_HEADERS})
    if (${OS} STREQUAL "Windows" AND ${COMPILER} STREQUAL "MinGW")
        # on Windows/gcc get rid of "lib" prefix for shared libraries,
        # and transform the ".dll.a" suffix into ".a" for import libraries
        set_target_properties(${EDOGINE_TARGET} PROPERTIES PREFIX "")
        set_target_properties(${EDOGINE_TARGET} PROPERTIES IMPORT_SUFFIX ".a")
    endif()
else()
    add_library(${EDOGINE_TARGET} STATIC ${EDOGINE_SOURCES} ${EDOGINE_HEADERS})
endif()

# Change the library output name
set_target_properties(${EDOGINE_TARGET} PROPERTIES OUTPUT_NAME "Edogine")

# Add the postfix "-d" for debug configurations
set_target_properties(${EDOGINE_TARGET} PROPERTIES DEBUG_POSTFIX -d)

# Set the output path for the library and runtime libraries
set_target_properties(${EDOGINE_TARGET} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/lib")
set_target_properties(${EDOGINE_TARGET} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/lib")
set_target_properties(${EDOGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/lib")
set_target_properties(${EDOGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/lib")
set_target_properties(${EDOGINE_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/bin")
set_target_properties(${EDOGINE_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/bin")

# Project propeties for IDEs
set_target_properties(${EDOGINE_TARGET} PROPERTIES PROJECT_LABEL "Edogine")

# Improve the visual studio project generation
source_group("Source Files\\Core" FILES ${CORE_SRC})
source_group("Source Files\\Graphics" FILES ${GRAPHICS_SRC})
source_group("Source Files\\System" FILES ${SYSTEM_SRC})
source_group("Header Files" FILES ${OTHER_HEADERS})
source_group("Header Files\\Core" FILES ${CORE_HEADERS})
source_group("Header Files\\Graphics" FILES ${GRAPHICS_HEADERS})
source_group("Header Files\\System" FILES ${SYSTEM_HEADERS})

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

find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIR})
    target_link_libraries(${EDOGINE_TARGET} ${SDL2_LIBRARY})
endif()

find_package(SDL2_image REQUIRED)
if(SDL2_IMAGE_FOUND)
    include_directories(${SDL2_IMAGE_INCLUDE_DIR})
    target_link_libraries(${EDOGINE_TARGET} ${SDL2_IMAGE_LIBRARY})
endif()

find_package(Box2D REQUIRED)
if(BOX2D_FOUND)
    include_directories(${BOX2D_INCLUDE_DIR})
    target_link_libraries(${EDOGINE_TARGET} ${BOX2D_LIBRARY})
endif()

# Install rules
install(TARGETS ${EDOGINE_TARGET} RUNTIME DESTINATION bin COMPONENT bin
                                  LIBRARY DESTINATION lib COMPONENT bin
                                  ARCHIVE DESTINATION lib COMPONENT bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION . COMPONENT devel)