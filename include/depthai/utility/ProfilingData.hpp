#pragma once

#include "depthai/utility/api.hpp"

namespace dai {

struct DEPTHAI_API ProfilingData {
    long long numBytesWritten;
    long long numBytesRead;
};

}  // namespace dai
