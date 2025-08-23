//
// Created by wang1 on 8/12/2025.
//

#ifndef VULKAN_PATH_TRACER_INSTANCE_H
#define VULKAN_PATH_TRACER_INSTANCE_H
#define APPLICATION_NAME "PathTracer"
#include <vulkan/vulkan.h>
#include <vector>

namespace Vulkan {

  class Instance final {
  public:

    explicit Instance(std::vector<const char*> layers);
    ~Instance();

    [[nodiscard]] VkInstance get() const {
      return instance;
    }

    [[nodiscard]] std::vector<VkPhysicalDevice> getDevices() const {
      return devices;
    }

  private:
    VkInstance instance{};
    std::vector<VkPhysicalDevice> devices;

    [[nodiscard]] static std::vector<const char*> getRequiredInstanceExtensions() ;
    [[nodiscard]] static bool isPhysicalDeviceSuitable(VkPhysicalDevice device);
    static bool checkValidationLayerSupport(const std::vector<const char*>& layers) ;
    void checkPhysicalDevice();

    static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
  };

} // Vulkan

#endif //VULKAN_PATH_TRACER_INSTANCE_H
