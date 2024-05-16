#include "Common.hpp"

#include "depthai/pipeline/node/host/Replay.hpp"

void bind_replay(pybind11::module& m, void* pCallstack){
    using namespace dai;
    using namespace node;

    auto replayVideo = ADD_NODE_DERIVED(ReplayVideo, ThreadedHostNode);
    auto replayMessage = ADD_NODE_DERIVED(ReplayMessage, ThreadedHostNode);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    // Call the rest of the type defines, then perform the actual bindings
    Callstack* callstack = (Callstack*) pCallstack;
    auto cb = callstack->top();
    callstack->pop();
    cb(m, pCallstack);
    // Actual bindings
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    // Node
    replayVideo.def_readonly("out", &ReplayVideo::out, DOC(dai, node, ReplayVideo, out))
        .def("setReplayMetadataFile", &ReplayVideo::setReplayMetadataFile, py::arg("replayFile"), DOC(dai, node, ReplayVideo, setReplayMetadataFile))
        .def("setReplayVideoFile", &ReplayVideo::setReplayVideoFile, py::arg("replayVideoFile"), DOC(dai, node, ReplayVideo, setReplayVideoFile))
        .def("setOutFrameType", &ReplayVideo::setOutFrameType, py::arg("frameType"), DOC(dai, node, ReplayVideo, setOutFrameType))
        .def("setSize", py::overload_cast<int, int>(&ReplayVideo::setSize), py::arg("width"), py::arg("height"), DOC(dai, node, ReplayVideo, setSize))
        .def("setSize", py::overload_cast<std::tuple<int, int>>(&ReplayVideo::setSize), py::arg("size"), DOC(dai, node, ReplayVideo, setSize))
        .def("setFps", &ReplayVideo::setFps, py::arg("fps"), DOC(dai, node, ReplayVideo, setFps))
        .def("setLoop", &ReplayVideo::setLoop, py::arg("loop"), DOC(dai, node, ReplayVideo, setLoop))
        .def("getReplayMetadataFile", &ReplayVideo::getReplayMetadataFile, DOC(dai, node, ReplayVideo, getReplayMetadataFile))
        .def("getReplayVideoFile", &ReplayVideo::getReplayVideoFile, DOC(dai, node, ReplayVideo, getReplayVideoFile))
        .def("getOutFrameType", &ReplayVideo::getOutFrameType, DOC(dai, node, ReplayVideo, getOutFrameType))
        .def("getSize", &ReplayVideo::getSize, DOC(dai, node, ReplayVideo, getSize))
        .def("getFps", &ReplayVideo::getFps, DOC(dai, node, ReplayVideo, getFps))
        .def("getLoop", &ReplayVideo::getLoop, DOC(dai, node, ReplayVideo, getLoop));

    replayMessage.def_readonly("out", &ReplayMessage::out, DOC(dai, node, ReplayMessage, out))
        .def("setReplayFile", &ReplayMessage::setReplayFile, py::arg("replayFile"), DOC(dai, node, ReplayMessage, setReplayFile))
        .def("setLoop", &ReplayMessage::setLoop, py::arg("loop"), DOC(dai, node, ReplayMessage, setLoop))
        .def("getReplayFile", &ReplayMessage::getReplayFile, DOC(dai, node, ReplayMessage, getReplayFile))
        .def("getLoop", &ReplayMessage::getLoop, DOC(dai, node, ReplayMessage, getLoop));
}