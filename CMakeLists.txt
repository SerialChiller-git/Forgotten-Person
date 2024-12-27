cmake_minimum_required(VERSION 3.28)
project(Forgotten_Person LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include(FetchContent)
# Fetch SFML
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)


FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.91.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG master
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ImGui-SFML)

# Include source directory
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/MapEditor)

# Collect source files
set(SOURCES 
    src/gameTile.cpp
)

# Create executable
add_executable(Forgotten_Person src/main.cpp ${SOURCES} )
add_executable(Editor src/MapEditor/editor.cpp)

# Link libraries
target_link_libraries(Forgotten_Person PRIVATE SFML::Graphics ImGui-SFML::ImGui-SFML)
target_link_libraries(Editor PRIVATE SFML::Graphics ImGui-SFML::ImGui-SFML)

# Copy assets after build
add_custom_command(
    TARGET Forgotten_Person POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/src/assets
    $<TARGET_FILE_DIR:Forgotten_Person>/assets
    COMMENT "Copying assets folder to runtime directory"
)
