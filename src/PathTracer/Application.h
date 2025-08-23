//
// Created by wang1 on 8/10/2025.
//

#ifndef VULKAN_PATH_TRACER_APPLICATION_H
#define VULKAN_PATH_TRACER_APPLICATION_H
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include "../Vulkan/Instance.h"
#include "../Vulkan/Window.h"
#include "../Vulkan/Device.h"
#include "../Vulkan/SwapChain.h"
#include "../Vulkan/GraphicsPipeline.h"

namespace PathTracer {
class Application final
{
public:
  Application();
  void run();

private:
  std::unique_ptr<Vulkan::Window> window;
  std::unique_ptr<Vulkan::Instance> instance;
  std::unique_ptr<Vulkan::Device> device;
  std::unique_ptr<Vulkan::Surface> surface;
  std::unique_ptr<Vulkan::SwapChain> swapChain;
  std::unique_ptr<Vulkan::GraphicsPipeline> graphicsPipeline;

  void createGraphicsPipeline();

  VkShaderModule createShaderModule(const std::vector<char> &code);
};
}


#endif //VULKAN_PATH_TRACER_APPLICATION_H
