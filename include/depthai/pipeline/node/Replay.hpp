#pragma once

#include <memory>

#include <depthai/pipeline/ThreadedNode.hpp>

// shared
#include <depthai/properties/XLinkOutProperties.hpp>

// project
#include <depthai/pipeline/datatype/Buffer.hpp>

#include <depthai/utility/RecordReplay.hpp>

namespace dai {
namespace node {

/**
 * @brief Replay node, used to replay a file to a source node
 */
class Replay : public NodeCRTP<ThreadedNode, Replay> {
private:
    std::shared_ptr<utility::VideoPlayer> videoPlayer;
    std::string replayFile;
   public:
    constexpr static const char* NAME = "Replay";
    void build();

    /**
     * Output for any type of messages to be transferred over XLink stream
     *
     * Default queue is blocking with size 8
     */
    Output out{true, *this, "out", Output::Type::MSender, {{DatatypeEnum::Buffer, true}}};

    void start() override;
    void run() override;
    void stop() override;

    Replay& setReplayFile(const std::string& replayFile);
};

}  // namespace node
}  // namespace dai