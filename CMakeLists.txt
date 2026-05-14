cmake_minimum_required(VERSION 3.15)
project(HBREngine LANGUAGES CXX)

# Force C++17 for modern features and clean library alignment
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for IDEs and tools that use them (like clang-tidy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Custom CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# 1. Define our source files
set(SOURCE_FILES
    src/main.cpp
    src/imgui.cpp
    src/imgui_draw.cpp
    src/imgui_tables.cpp
    src/imgui_widgets.cpp
    src/imgui_impl_glfw.cpp
    src/imgui_impl_opengl3.cpp
)

# 2. Create the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# 3. Include our local headers directory
target_include_directories(${PROJECT_NAME} PRIVATE include)

# 4. Find GLFW (Required on both Mac and Windows)
find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# 5. OS-Specific Configurations (The Cross-Platform Magic)
if(APPLE)
    # macOS Specifics
    find_library(COCOA_FRAMEWORK Cocoa REQUIRED)
    find_library(OPENGL_FRAMEWORK OpenGL REQUIRED)
    find_library(IOKIT_FRAMEWORK IOKit REQUIRED)
    find_library(COREVIDEO_FRAMEWORK CoreVideo REQUIRED)
    
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        ${COCOA_FRAMEWORK} 
        ${OPENGL_FRAMEWORK} 
        ${IOKIT_FRAMEWORK} 
        ${COREVIDEO_FRAMEWORK}
    )
    
    # Define a macro so your code knows it is running on Mac (useful for OpenGL 4.1 switches)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENGINE_PLATFORM_MAC)

elseif(WIN32)
    # Windows Specifics
    # On Windows, we need GLEW to map the modern OpenGL function pointers
    # Windows: use static runtime to avoid DLL hell
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    find_package(GLEW REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
    
    # Prevent Windows.h from defining annoying min/max macros that break GLM
    target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
endif()

# Copy runtime assets and shaders to the runtime binary directory on every build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMENT "Synchronizing shaders and asset directories to output bundle..."
)

# Compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()