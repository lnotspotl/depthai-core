#pragma once

#include "depthai/modelzoo/NNModelDescription.hpp"
#include "depthai/nn_archive/NNArchive.hpp"

namespace dai {

class ZooManager {
   public:
    ZooManager(const NNModelDescription& modelDescription) : modelDescription(modelDescription) {}

    /**
     * @brief Compute hash based on name, version and platform
     *
     * @return size_t: Hash value
     */
    size_t computeModelHash() const;

    /**
     * @brief Get cache folder name
     *
     * @return std::string: Cache folder name
     */
    std::string getCacheFolderName() const;

    /**
     * @brief Get cache folder name in specified cache directory
     *
     * @param cacheDir: Cache directory, default is "."
     * @return std::string: Cache folder name
     */
    std::string getCacheFolderPath(const std::string& cacheDir = ".") const;

    /**
     * @brief Combine two paths
     *
     * @param path1: First path
     * @param path2: Second path
     * @return std::string: Combined path
     */
    std::string combinePaths(const std::string& path1, const std::string& path2) const;

    /**
     * @brief Create cache folder
     */
    void createCacheFolder() const;

    /**
     * @brief Remove cache folder
     */
    void removeCacheFolder() const;

    /**
     * @brief Check if model is cached
     *
     * @return bool: True if model is cached
     */
    bool isCached() const;

    /**
     * @brief Check if path exists
     *
     * @param path: Path to check
     * @return bool: True if path exists
     */
    bool checkExists(const std::string& path) const;

    /**
     * @brief Download model from model zoo
     */
    void downloadModel();

    /**
     * @brief Load model from cache
     *
     * @return NNArchive: Model archive
     */
    NNArchive loadModelFromCache() const;

   private:
    const NNModelDescription& modelDescription;
};

NNArchive getModelFromZoo(const NNModelDescription& modelDescription, bool useCached = true);

}  // namespace dai