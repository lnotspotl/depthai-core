#pragma once

#include <depthai/pipeline/DeviceNode.hpp>

// shared
#include <depthai/properties/XLinkOutProperties.hpp>

namespace dai {
namespace node {

/**
 * @brief XLinkOut node. Sends messages over XLink.
 */
class XLinkOut : public DeviceNodeCRTP<DeviceNode, XLinkOut, XLinkOutProperties> {
   public:
    constexpr static const char* NAME = "XLinkOut";
    using DeviceNodeCRTP::DeviceNodeCRTP;
    std::shared_ptr<XLinkOut> build();

   public:
    /**
     * Input for any type of messages to be transferred over XLink stream
     *
     * Default queue is blocking with size 8
     */
    // Input input{*this, "in", Input::Type::SReceiver, true, 8, {{DatatypeEnum::Buffer, true}}};
    Input input{*this, {.name = "in", .types = {{DatatypeEnum::Buffer, true}}}};

    /**
     * Specifies XLink stream name to use.
     *
     * The name should not start with double underscores '__',
     * as those are reserved for internal use.
     * @param name Stream name
     */
    void setStreamName(const std::string& name);

    /**
     * Specifies a message sending limit. It's approximated from specified rate.
     *
     * @param fps Approximate rate limit in messages per second
     */
    void setFpsLimit(float fps);

    /**
     * Specify whether to transfer only messages attributes and not buffer data
     */
    void setMetadataOnly(bool metadataOnly);

    /// Get stream name
    std::string getStreamName() const;
    /// Get rate limit in messages per second
    float getFpsLimit() const;
    /// Get whether to transfer only messages attributes and not buffer data
    bool getMetadataOnly() const;

   protected:
    bool isBuild = false;
    bool needsBuild() override { return !isBuild; }
};

}  // namespace node
}  // namespace dai
