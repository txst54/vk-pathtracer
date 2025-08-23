//
// Created by wang1 on 8/12/2025.
//

#include <vulkan/vulkan_core.h>
#include "Window.h"

namespace Vulkan {
  Window::Window() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_NAME, nullptr, nullptr);
  }

  Window::~Window() {
    if (window != nullptr) {
      glfwDestroyWindow(window);
      window = nullptr;
    }
    glfwTerminate();
  }

  VkExtent2D Window::getFramebufferSize() const
  {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    return VkExtent2D{ static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
  }
} // Vulkan