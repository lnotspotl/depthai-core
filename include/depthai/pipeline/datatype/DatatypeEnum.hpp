#pragma once

#include <cstdint>

#include "depthai/utility/api.hpp"

namespace dai {

enum class DatatypeEnum : std::int32_t {
    ADatatype,
    Buffer,
    ImgFrame,
    EncodedFrame,
    NNData,
    ImageManipConfig,
    CameraControl,
    ImgDetections,
    SpatialImgDetections,
    SystemInformation,
    SystemInformationS3,
    SpatialLocationCalculatorConfig,
    SpatialLocationCalculatorData,
    EdgeDetectorConfig,
    AprilTagConfig,
    AprilTags,
    Tracklets,
    IMUData,
    StereoDepthConfig,
    FeatureTrackerConfig,
    ThermalConfig,
    ToFConfig,
    TrackedFeatures,
    BenchmarkReport,
    MessageGroup,
    TransformData,
    PointCloudConfig,
    PointCloudData,
    RGBDData,
    ImageAlignConfig,
    ImgAnnotations,
    ImageFiltersConfig,
    ToFDepthConfidenceFilterConfig,
    ObjectTrackerConfig,
    DynamicCalibrationControl,
    DynamicCalibrationResult,
    CalibrationQuality,
    CoverageData,
};
DEPTHAI_API bool isDatatypeSubclassOf(DatatypeEnum parent, DatatypeEnum children);

}  // namespace dai
