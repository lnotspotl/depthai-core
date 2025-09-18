// https://herbsutter.com/gotw/_101/

#pragma once

#include "depthai/utility/api.hpp"

#include <memory>

namespace dai {

template <typename T>
class DEPTHAI_API Pimpl {
   private:
    std::unique_ptr<T> m;

   public:
    Pimpl();
    template <typename... Args>
    Pimpl(Args&&...);
    ~Pimpl();
    T* operator->();
    T& operator*();
};

}  // namespace dai
