//
// Created by wang1 on 8/10/2025.
//

#include "Application.h"
#include <GLFW/glfw3.h>

#include <memory>
#include <stdexcept>
#include <fstream>

namespace PathTracer {
  Application::Application() {
#ifdef NDEBUG
    std::vector<const char*> layers = {};
#else
    std::vector<const char*> layers = { "VK_LAYER_KHRONOS_validation" };
#endif

    window = std::make_unique<Vulkan::Window>();
    instance = std::make_unique<Vulkan::Instance>(layers);
    surface = std::make_unique<Vulkan::Surface>(*instance, *window);
    device = std::make_unique<Vulkan::Device>(instance->getDevices().front(), *surface);
    swapChain = std::make_unique<Vulkan::SwapChain>(*device, *window);
    graphicsPipeline = std::make_unique<Vulkan::GraphicsPipeline>(*device, *swapChain);
  }

  void Application::run() {
    while (!glfwWindowShouldClose(window->get())) {
      glfwPollEvents();
    }
  }
}