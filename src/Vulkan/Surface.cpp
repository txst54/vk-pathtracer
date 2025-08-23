//
// Created by wang1 on 8/14/2025.
//

#include "Surface.h"
#include "Vulkan.h"

namespace Vulkan {
  Surface::Surface(const Instance& instance, const Window& window): instance(instance), window(window) {
    VK_CHECK(glfwCreateWindowSurface(instance.get(), window.get(), nullptr, &surface),
             "Create window surface");
  }

  Surface::~Surface()
  {
    if (surface != nullptr)
    {
      vkDestroySurfaceKHR(instance.get(), surface, nullptr);
      surface = nullptr;
    }
  }
} // Vulkan