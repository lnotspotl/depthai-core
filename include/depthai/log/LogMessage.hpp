#pragma once

#include "depthai/utility/api.hpp"

// std
#include <cstdint>

// project
#include "LogLevel.hpp"
#include "depthai/common/Timestamp.hpp"
#include "depthai/utility/Serialization.hpp"

namespace dai {

struct DEPTHAI_API LogMessage {
    std::string nodeIdName;
    LogLevel level{LogLevel::TRACE};
    Timestamp time;
    size_t colorRangeStart{0};
    size_t colorRangeEnd{0};
    std::string payload;
};

DEPTHAI_SERIALIZE_EXT(LogMessage, nodeIdName, level, time, colorRangeStart, colorRangeEnd, payload);

}  // namespace dai
