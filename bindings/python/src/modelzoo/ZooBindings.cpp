#include "ZooBindings.hpp"

// depthai
#include "depthai/modelzoo/Zoo.hpp"

void ZooBindings::bind(pybind11::module& m, void* pCallstack) {
    using namespace dai;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    // Call the rest of the type defines, then perform the actual bindings
    Callstack* callstack = (Callstack*)pCallstack;
    auto cb = callstack->top();
    callstack->pop();
    cb(m, pCallstack);
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////

    m.def("getModelFromZoo",
          dai::getModelFromZoo,
          py::arg("modelDescription"),
          py::arg("cacheDirectory") = ".",
          py::arg("useCached") = true,
          py::arg("cacheModel") = true,
          DOC(dai, getModelFromZoo));

    m.def("downloadModelsFromZoo",
          dai::downloadModelsFromZoo,
          py::arg("path"),
          py::arg("cacheDirectory"),
          py::arg("verbose") = false,
          DOC(dai, downloadModelsFromZoo));
}
