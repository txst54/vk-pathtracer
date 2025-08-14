@echo off
cmake -B bin -S . -G "Visual Studio 17 2022" -A x64 ^
  -DCMAKE_TOOLCHAIN_FILE=C:/users/wang1/documents/github/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build bin --config Release
pause
