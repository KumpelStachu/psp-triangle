cmake_minimum_required(VERSION 3.0)

project(shapes)

add_executable(${PROJECT_NAME} main.cpp)

find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2main
)
create_pbp_file(
    TARGET ${PROJECT_NAME}
    ICON_PATH NULL
    BACKGROUND_PATH NULL
    PREVIEW_PATH NULL
    TITLE ${PROJECT_NAME}
)