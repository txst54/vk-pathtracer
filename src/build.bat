@echo off
glslc Shaders/Triangle/shader.vert -o bin/vert.spv
glslc Shaders/Triangle/shader.frag -o bin/frag.spv
cmake -B bin -S . -G "Visual Studio 17 2022" -A x64 ^
  -DCMAKE_TOOLCHAIN_FILE=C:/users/wang1/documents/github/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build bin --config Release
pause
