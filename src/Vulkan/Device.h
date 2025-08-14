//
// Created by wang1 on 8/13/2025.
//

#ifndef VULKAN_PATH_TRACER_DEVICE_H
#define VULKAN_PATH_TRACER_DEVICE_H
#include <optional>

namespace Vulkan {
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
  };

  struct QueueIndices {
    QueueFamily graphicsQueue{};
    QueueFamily computeQueue{};

    [[nodiscard]] std::vector<VkDeviceQueueCreateInfo> getQueueCreateInfos() const {
      std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};
#define ADD_QUEUE_INFO(q) if (q.isComplete()) queueCreateInfos.push_back(q.queueCreateInfo);
      ADD_QUEUE_INFO(graphicsQueue);
      ADD_QUEUE_INFO(computeQueue);
      return queueCreateInfos;
    }

    void getDeviceQueues(VkDevice& device) {
#define GET_DEVICE_QUEUE(q) if (q.isComplete()) vkGetDeviceQueue(device, q.family.value(), 0, &q.queue)
      GET_DEVICE_QUEUE(graphicsQueue);
      GET_DEVICE_QUEUE(computeQueue);
    }
  };

  class Device {
  public:
    explicit Device(VkPhysicalDevice device);
    ~Device();

  private:
    VkPhysicalDevice physicalDevice;
    QueueIndices queueIndices{};
    VkDevice device{};

    std::vector<QueueFamily> findQueueFamilies(VkPhysicalDevice device, const float *queuePriority);
  };

} // Vulkan

#endif //VULKAN_PATH_TRACER_DEVICE_H
