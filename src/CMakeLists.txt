cmake_minimum_required(VERSION 3.22)
project(vulkan_path_tracer)

find_package(Vulkan REQUIRED)
find_package(GLFW3 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(exe_name
        out
)

set(src_files_vulkan
        Vulkan/Instance.cpp
        Vulkan/Instance.h
        Vulkan/Window.cpp
        Vulkan/Window.h
        Vulkan/Vulkan.cpp
        Vulkan/Vulkan.h
        Vulkan/Device.cpp
        Vulkan/Device.h
)

set(src_files_pathtracer
        PathTracer/Application.cpp
        PathTracer/Application.h
)

set(src_files
        main.cpp
        PathTracer/Application.h
)
add_executable(${exe_name}
        ${src_files_vulkan}
        ${src_files_pathtracer}
        ${src_files}
)

target_link_libraries(${exe_name} PRIVATE glfw Vulkan::Vulkan)
