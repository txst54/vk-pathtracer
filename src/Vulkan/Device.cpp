//
// Created by wang1 on 8/13/2025.
//

#include <vulkan/vulkan.h>
#include <vector>
#include "Device.h"
#include "Vulkan.h"

namespace Vulkan {
  Device::Device(VkPhysicalDevice physicalDevice, const Surface& surface) :
    physicalDevice(physicalDevice), surface(surface)
  {
    float queuePriority = 1.0;
    findQueueFamilies(physicalDevice, &queuePriority);
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos = queueIndices.getQueueCreateInfos();

    VkPhysicalDeviceFeatures deviceFeatures{};
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = 1;

    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    createInfo.enabledLayerCount = 0;

    VK_CHECK(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device), "Create Vulkan logical device");
    queueIndices.getPresentQueue(physicalDevice, device, surface);
    queueIndices.getDeviceQueues(device);
  }

  Device::~Device() {
    if (device != nullptr) {
      vkDestroyDevice(device, nullptr);
      device = nullptr;
    }
  }

  void Device::findQueueFamilies(VkPhysicalDevice device, const float* queuePriority) {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
      if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
        queueIndices.graphicsQueue.setIndex(static_cast<uint32_t>(i), queuePriority);
      } else if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) {
        queueIndices.computeQueue.setIndex(static_cast<uint32_t>(i), queuePriority);
      }
      i++;
    }
  }
} // Vulkan