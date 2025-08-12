//
// Created by wang1 on 8/12/2025.
//

#ifndef VULKAN_PATH_TRACER_WINDOW_H
#define VULKAN_PATH_TRACER_WINDOW_H

#include <GLFW/glfw3.h>
#define WIDTH 1920
#define HEIGHT 1080
#define WINDOW_NAME "PathTracer"

namespace Vulkan {

  class Window final {
  public:
    Window();
    ~Window();

    [[nodiscard]] GLFWwindow* get() const {
      return window;
    }

  private:
    GLFWwindow *window;
  };

} // Vulkan

#endif //VULKAN_PATH_TRACER_WINDOW_H
