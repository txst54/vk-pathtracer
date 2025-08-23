//
// Created by wang1 on 8/20/2025.
//

#include <vector>
#include <string>
#include <fstream>
#include "Util.h"

namespace Vulkan {
  std::vector<char> Util::readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
      throw std::runtime_error("failed to open file!");
    }

    std::streamsize fileSize = (std::streamsize) file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
  }
} // Vulkan