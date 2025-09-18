// IWYU pragma: private, include "depthai/depthai.hpp"
#pragma once

#include "depthai/utility/api.hpp"

#include <string>

namespace dai {

DEPTHAI_API bool initialize();
DEPTHAI_API bool initialize(std::string additionalInfo, bool installSignalHandler = true, void* javavm = nullptr);
DEPTHAI_API bool initialize(const char* additionalInfo, bool installSignalHandler = true, void* javavm = nullptr);
DEPTHAI_API bool initialize(void* javavm);

}  // namespace dai
