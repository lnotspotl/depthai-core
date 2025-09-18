#pragma once

#ifdef _WIN32
  #ifdef DEPTHAI_BUILD
    #define DEPTHAI_API __declspec(dllexport)
  #else
    #define DEPTHAI_API __declspec(dllimport)
  #endif
#else
  #define DEPTHAI_API
#endif