//
// Created by wang1 on 8/10/2025.
//

#include "Application.h"
#include <GLFW/glfw3.h>

#include <memory>

namespace PathTracer {
  Application::Application() {
#ifdef NDEBUG
    std::vector<const char*> layers = {};
#else
    std::vector<const char*> layers = { "VK_LAYER_KHRONOS_validation" };
#endif

    window = std::make_unique<Vulkan::Window>();
    instance = std::make_unique<Vulkan::Instance>(layers);
    device = std::make_unique<Vulkan::Device>(instance->getDevices().front());
  }

  void Application::run() {
    while (!glfwWindowShouldClose(window->get())) {
      glfwPollEvents();
    }
  }
}