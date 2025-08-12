//
// Created by wang1 on 8/10/2025.
//

#include "Application.h"
#include <GLFW/glfw3.h>

namespace PathTracer {
  Application::Application() {
#ifdef NDEBUG
    std::vector<const char*> layers = {};
#else
    std::vector<const char*> layers = { "VK_LAYER_KHRONOS_validation" };
#endif

    window.reset(new Vulkan::Window());
    instance.reset(new Vulkan::Instance(layers));
  }

  void Application::run() {
    while (!glfwWindowShouldClose(window->get())) {
      glfwPollEvents();
    }
  }
}