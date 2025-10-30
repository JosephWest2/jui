cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE Debug)

set(SDL_SOURCE_DIR external/sdl)
set(SDL_TTF_SOURCE_DIR external/sdl_ttf)
set(SDL_IMAGE_SOURCE_DIR external/sdl_image)
set(ABSEIL_SOURCE_DIR external/abseil)
set(PROJECT_NAME jui)

project(${PROJECT_NAME} VERSION 0.1)

file (GLOB_RECURSE 
    SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})

add_subdirectory(${SDL_SOURCE_DIR})
add_subdirectory(${SDL_TTF_SOURCE_DIR})
add_subdirectory(${SDL_IMAGE_SOURCE_DIR})
add_subdirectory(${ABSEIL_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    SDL3_image::SDL3_image
    absl::flat_hash_map
)
target_include_directories(${PROJECT_NAME}
    PRIVATE ${SDL_SOURCE_DIR}/include
    PRIVATE ${SDL_TTF_SOURCE_DIR}/include
    PRIVATE ${SDL_IMAGE_SOURCE_DIR}/include
    PRIVATE src
)
