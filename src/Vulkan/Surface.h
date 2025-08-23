//
// Created by wang1 on 8/14/2025.
//

#ifndef VULKAN_PATH_TRACER_SURFACE_H
#define VULKAN_PATH_TRACER_SURFACE_H

#include "Instance.h"
#include "Window.h"

namespace Vulkan {

  class Surface final {
  public:
    explicit Surface(const Instance& instance, const Window& window);
    ~Surface();

    [[nodiscard]] VkSurfaceKHR get() const {
      return surface;
    }

    [[nodiscard]] Instance getInstance() const {
      return instance;
    }

    [[nodiscard]] Window getWindow() const {
      return window;
    }

  private:
    VkSurfaceKHR surface{};
    const Instance& instance;
    const Window& window;
  };

} // Vulkan

#endif //VULKAN_PATH_TRACER_SURFACE_H
