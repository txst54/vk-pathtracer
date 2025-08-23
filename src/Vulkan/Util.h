//
// Created by wang1 on 8/20/2025.
//

#ifndef VULKAN_PATH_TRACER_UTIL_H
#define VULKAN_PATH_TRACER_UTIL_H

namespace Vulkan {

  class Util {
  public:
    static std::vector<char> readFile(const std::string& filename);
  };

} // Vulkan

#endif //VULKAN_PATH_TRACER_UTIL_H
