//
// Created by wang1 on 8/15/2025.
//

#ifndef VULKAN_PATH_TRACER_SWAPCHAIN_H
#define VULKAN_PATH_TRACER_SWAPCHAIN_H

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include "Surface.h"
#include "Device.h"
#include "ImageView.h"

namespace Vulkan {
  struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
  };

  class SwapChain {
  public:
    SwapChain(const Device& device, const Window& window);
    ~SwapChain();
  private:
    const Surface& surface;
    const Window& window;
    const Device& device;
    std::vector<VkImage> images;
    std::vector<std::unique_ptr<ImageView>> imageViews;
    VkSwapchainKHR swapChain;
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice physicalDevice) const;
    static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

    [[nodiscard]] VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities) const;

    static uint32_t chooseImageCount(const VkSurfaceCapabilitiesKHR &capabilities);
  public:
    uint32_t minImageCount{};
    VkPresentModeKHR presentMode{};
    VkFormat format{};
    VkExtent2D extent{};

    void createImageViews();
  };

} // Vulkan

#endif //VULKAN_PATH_TRACER_SWAPCHAIN_H
