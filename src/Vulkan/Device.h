//
// Created by wang1 on 8/13/2025.
//

#ifndef VULKAN_PATH_TRACER_DEVICE_H
#define VULKAN_PATH_TRACER_DEVICE_H
#include <optional>
#include "Surface.h"

namespace Vulkan {
  static const std::vector<const char*> deviceExtensions = {
      VK_KHR_SWAPCHAIN_EXTENSION_NAME
  };

  struct QueueFamily {
    std::optional<uint32_t> family;
    VkQueue queue{};
    VkDeviceQueueCreateInfo queueCreateInfo{};

    [[nodiscard]] bool isComplete() const {
      return family.has_value();
    }

    void setIndex(uint32_t index, const float* queuePriority) {
      family = index;
      queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      queueCreateInfo.queueFamilyIndex = family.value();
      queueCreateInfo.queueCount = 1;
      queueCreateInfo.pQueuePriorities = queuePriority;
    }

    void setPresentQueue(QueueFamily candidateQueue, VkPhysicalDevice& physicalDevice,
                         VkDevice& device, const Surface& surface) {
      if (!candidateQueue.isComplete()) {
        return;
      }
      uint32_t candidateFamily = candidateQueue.family.value();
      VkBool32 presentSupport = VK_FALSE;
      vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, candidateFamily, surface.get(), &presentSupport);
      if (presentSupport) {
        vkGetDeviceQueue(device, candidateFamily, 0, &queue);
        family = candidateFamily;
      }
    }
  };

  struct QueueIndices {
    QueueFamily graphicsQueue{};
    QueueFamily computeQueue{};
    QueueFamily presentQueue{};

    [[nodiscard]] std::vector<VkDeviceQueueCreateInfo> getQueueCreateInfos() const {
      std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};
#define ADD_QUEUE_INFO(q) if (q.isComplete()) queueCreateInfos.push_back(q.queueCreateInfo);
      ADD_QUEUE_INFO(graphicsQueue);
      ADD_QUEUE_INFO(computeQueue);
      return queueCreateInfos;
    }

    void getPresentQueue(VkPhysicalDevice& physicalDevice, VkDevice& device, const Surface& surface) {
      presentQueue.setPresentQueue(graphicsQueue, physicalDevice, device, surface);
      presentQueue.setPresentQueue(computeQueue, physicalDevice, device, surface);
    }

    void getDeviceQueues(VkDevice& device) {
#define GET_DEVICE_QUEUE(q) if (q.isComplete()) vkGetDeviceQueue(device, q.family.value(), 0, &q.queue)
      GET_DEVICE_QUEUE(graphicsQueue);
      GET_DEVICE_QUEUE(computeQueue);
      GET_DEVICE_QUEUE(presentQueue);
    }
  };

  class Device final {
  public:
    QueueIndices queueIndices{};

    explicit Device(VkPhysicalDevice device, const Surface& surface);
    ~Device();

    [[nodiscard]] VkDevice get() const {
      return device;
    }

    [[nodiscard]] VkPhysicalDevice getPhysicalDevice() const {
      return physicalDevice;
    }

    [[nodiscard]] const Surface& getSurface() const {
      return surface;
    }

  private:
    VkPhysicalDevice physicalDevice;
    VkDevice device{};
    const Surface& surface;

    void findQueueFamilies(VkPhysicalDevice device, const float *queuePriority);
  };

} // Vulkan

#endif //VULKAN_PATH_TRACER_DEVICE_H
