//
// Created by wang1 on 8/15/2025.
//

#include <algorithm>
#include "SwapChain.h"
#include "Vulkan.h"

namespace Vulkan {
  SwapChain::SwapChain(const Device& device, const Window& window):
    device(device), surface(device.getSurface()), window(window)
  {
    const auto swapChainSupport = querySwapChainSupport(device.getPhysicalDevice());

    VkPresentModeKHR presentModeKhr = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkExtent2D extentKhr = chooseSwapExtent(swapChainSupport.capabilities);
    uint32_t imageCount = chooseImageCount(swapChainSupport.capabilities);

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface.get();
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extentKhr;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentModeKhr;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = nullptr;

    if (device.queueIndices.graphicsQueue.family != device.queueIndices.presentQueue.family)
    {
      uint32_t queueFamilyIndices[] = { device.queueIndices.graphicsQueue.family.value(), device.queueIndices.presentQueue.family.value() };

      createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
      createInfo.queueFamilyIndexCount = 2;
      createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else
    {
      createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
      createInfo.queueFamilyIndexCount = 0; // Optional
      createInfo.pQueueFamilyIndices = nullptr; // Optional
    }

    VK_CHECK(vkCreateSwapchainKHR(device.get(), &createInfo, nullptr, &swapChain), "Create swap chain");

    vkGetSwapchainImagesKHR(device.get(), swapChain, &imageCount, nullptr);
    images.resize(imageCount);
    vkGetSwapchainImagesKHR(device.get(), swapChain, &imageCount, images.data());

    minImageCount = swapChainSupport.capabilities.minImageCount;
    presentMode = presentModeKhr;
    format = surfaceFormat.format;
    extent = extentKhr;

    createImageViews();
  }

  SwapChainSupportDetails SwapChain::querySwapChainSupport(VkPhysicalDevice physicalDevice) const
  {
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface.get(), &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface.get(), &formatCount, nullptr);

    if (formatCount != 0)
    {
      details.formats.resize(formatCount);
      vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface.get(), &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface.get(), &presentModeCount, nullptr);

    if (presentModeCount != 0)
    {
      details.presentModes.resize(presentModeCount);
      vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface.get(), &presentModeCount,
                                                details.presentModes.data());
    }

    return details;
  }

  SwapChain::~SwapChain() {
    if (swapChain != nullptr) {
      vkDestroySwapchainKHR(device.get(), swapChain, nullptr);
      swapChain = nullptr;
    }
  }

  VkSurfaceFormatKHR SwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
  {
    if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED)
    {
      return { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
    }

    for (const auto& availableFormat : availableFormats)
    {
      if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace ==
                                                                VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
      {
        return availableFormat;
      }
    }

    return availableFormats[0];
  }

  VkPresentModeKHR SwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
  {
    for (const auto& availablePresentMode : availablePresentModes)
    {
      if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
      {
        return availablePresentMode;
      }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
  }

  uint32_t SwapChain::chooseImageCount(const VkSurfaceCapabilitiesKHR& capabilities)
  {
    uint32_t imageCount = capabilities.minImageCount;

    if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount)
    {
      imageCount = capabilities.maxImageCount;
    }

    return imageCount;
  }

  VkExtent2D SwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const
  {
    if (capabilities.currentExtent.width != UINT32_MAX)
    {
      return capabilities.currentExtent;
    }

    auto actualExtent = window.getFramebufferSize();
    actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width,
                                    capabilities.maxImageExtent.width);
    actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height,
                                     capabilities.maxImageExtent.height);
    return actualExtent;
  }

  void SwapChain::createImageViews()
  {
    for (auto* const image : images)
    {
      imageViews.
          push_back(std::make_unique<ImageView>(device, image, format));
    }
  }

} // Vulkan