cmake_minimum_required(VERSION 3.22)
project(vulkan_path_tracer)

find_package(Vulkan REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

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

target_include_directories(${exe_name} PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(${exe_name} PRIVATE ${GLFW_LIBRARIES} Vulkan::Vulkan)
