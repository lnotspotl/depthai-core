#pragma once

#include "depthai/utility/api.hpp"

// std
#include <cstdint>

// project
#include "depthai/utility/Serialization.hpp"

namespace dai {

// Follows spdlog levels
enum class DEPTHAI_API LogLevel : std::int32_t { TRACE = 0, DEBUG, INFO, WARN, ERR, CRITICAL, OFF };

}  // namespace dai
