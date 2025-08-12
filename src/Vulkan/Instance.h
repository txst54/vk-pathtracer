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

    Instance(std::vector<const char*> layers);
    ~Instance();

    [[nodiscard]] VkInstance get() const {
      return instance;
    }

  private:
    VkInstance instance{};

    std::vector<const char*> getRequiredInstanceExtensions() const;
    bool checkValidationLayerSupport(std::vector<const char*> layers) const;
  };

} // Vulkan

#endif //VULKAN_PATH_TRACER_INSTANCE_H
