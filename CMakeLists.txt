cmake_minimum_required(VERSION 3.20)
project(QBackTest)

set(CMAKE_CXX_STANDARD 17)
include(FetchContent)

# download and configure the glad project
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)
FetchContent_MakeAvailable(glad)
FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    FetchContent_Populate(glad)
    set(
            GLAD_PROFILE "core"
            CACHE STRING "OpenGL profile"
    )
    set(
            GLAD_API "gl=4.6"
            CACHE STRING "API type/version pairs, "
            "like \"gl=3.2,gles=\", no version means latest"
    )
    set(
            GLAD_GENERATOR "c"
            CACHE STRING "Language to generate the binding for")
    add_subdirectory(
            ${glad_SOURCE_DIR}
            ${glad_BINARY_DIR}
    )
endif()

# download and configure the GLFW project
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
)
FetchContent_MakeAvailable(glfw)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_DOCS     off CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS    off CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES off CACHE BOOL "" FORCE)

    add_subdirectory(
            ${glfw_SOURCE_DIR}
            ${glfw_BINARY_DIR}
    )
endif()

# download the Dear ImGUI project
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
)
FetchContent_MakeAvailable(imgui)
FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
    add_subdirectory(
            ${imgui_SOURCE_DIR}
    )
endif()

# Dear ImGui library configuration
add_library(
        imgui
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
)

target_compile_options(
        imgui PRIVATE
        -DIMGUI_IMPL_OPENGL_LOADER_GLAD
)

target_include_directories(
        imgui PRIVATE
        ${imgui_SOURCE_DIR}
        ${glad_BINARY_DIR}/include
        ${glfw_SOURCE_DIR}/include
)

# Fast CSV
FetchContent_Declare(
        rapid-csv
        GIT_REPOSITORY https://github.com/d99kris/rapidcsv.git
        GIT_TAG v8.53
)
FetchContent_MakeAvailable(rapid-csv)
FetchContent_GetProperties(rapid-csv)
if(NOT rapid-csv_POPULATED)
    FetchContent_Populate(rapid-csv)
    add_subdirectory(
            ${rapid-csv_SOURCE_DIR}
    )
endif()

find_package(OpenGL REQUIRED)  # for Dear ImGui
find_package(Threads REQUIRED) # for GLFW
find_package(X11 REQUIRED)     # for GLFW

add_executable(QBackTest main.cpp src/Handlers/DataEngine/DataEngine.cpp)

target_include_directories(
        QBackTest PRIVATE
        ${OPENGL_INCLUDE_DIR}
        ${glad_BINARY_DIR}/include
        ${glfw_SOURCE_DIR}/include
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
        ${imgui_SOURCE_DIR}/misc/cpp
        ${rapid-csv_SOURCE_DIR}/src
        lib/L2DFileDialog
)

target_link_libraries(
        QBackTest PRIVATE
        imgui
        glad
        glfw
        ${OPENGL_LIBRARY}
)