//
// Created by wang1 on 8/20/2025.
//

#ifndef VULKAN_PATH_TRACER_IMAGEVIEW_H
#define VULKAN_PATH_TRACER_IMAGEVIEW_H

#include <vulkan/vulkan.h>
#include "Device.h"

namespace Vulkan {

  class ImageView {
  public:
    ImageView(const Device& device, VkImage image, VkFormat format);
    ImageView(const Device& device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    ~ImageView();

    [[nodiscard]] VkImageView Get() const
    {
      return imageView;
    }

    [[nodiscard]] VkFormat GetFormat() const
    {
      return format;
    }

    [[nodiscard]] VkImage GetImage() const
    {
      return image;
    }

    [[nodiscard]] const class Device& GetDevice() const
    {
      return device;
    }

  private:
    VkImageView imageView;
    const Device& device;
    const VkImage image;
    const VkFormat format;
  };

} // Vulkan

#endif //VULKAN_PATH_TRACER_IMAGEVIEW_H
