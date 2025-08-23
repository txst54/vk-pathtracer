//
// Created by wang1 on 8/20/2025.
//

#ifndef VULKAN_PATH_TRACER_GRAPHICSPIPELINE_H
#define VULKAN_PATH_TRACER_GRAPHICSPIPELINE_H

#include <vulkan/vulkan.h>
#include <vector>
#include "Device.h"
#include "SwapChain.h"

namespace Vulkan {

  class GraphicsPipeline {
  public:
    explicit GraphicsPipeline(Device& device, SwapChain& swapChain);
    ~GraphicsPipeline();
  private:
    const Device& device;
    const SwapChain& swapChain;
    VkPipeline pipeline{};
    VkPipelineLayout pipelineLayout{};
    VkShaderModule vertShaderModule{};
    VkShaderModule fragShaderModule{};
    VkShaderModule GraphicsPipeline::createShaderModule(const std::vector<char>& code);
  };

} // Vulkan

#endif //VULKAN_PATH_TRACER_GRAPHICSPIPELINE_H
