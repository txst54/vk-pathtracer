//
// Created by wang1 on 8/12/2025.
//

#ifndef VULKAN_PATH_TRACER_VULKAN_H
#define VULKAN_PATH_TRACER_VULKAN_H

#include <vulkan/vulkan.h>
#include <string>

namespace Vulkan {
  std::string VK_DEVICE_TYPE(VkPhysicalDeviceType type);
  void VK_CHECK(VkResult result, const char* operation);
} // Vulkan

#endif //VULKAN_PATH_TRACER_VULKAN_H
