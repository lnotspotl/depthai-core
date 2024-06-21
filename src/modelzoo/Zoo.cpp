#include "depthai/modelzoo/Zoo.hpp"

#include <cpr/cpr.h>

#include <depthai/utility/Path.hpp>
#include <iostream>

namespace dai {

size_t ZooManager::computeModelHash() const {
    std::hash<std::string> hasher;
    return hasher(modelDescription.getModelSlug() + modelDescription.getModelInstanceSlug() + modelDescription.getPlatform());
}

std::string ZooManager::getModelCacheFolderName() const {
    size_t hash = computeModelHash();
    std::string hashstr = std::to_string(hash);
    return modelDescription.getModelSlug() + "_" + modelDescription.getModelInstanceSlug() + "_" + modelDescription.getPlatform() + "_" + hashstr;
}

std::string ZooManager::getModelCacheFolderPath(const std::string& cacheDirectory) const {
    return combinePaths(cacheDirectory, getModelCacheFolderName());
}

std::string ZooManager::combinePaths(const std::string& path1, const std::string& path2) const {
#if defined(_WIN32) && defined(_MSC_VER)
    const std::string separator = "\\";
#else
    const std::string separator = "/";
#endif
    return path1 + separator + path2;
}

void ZooManager::createCacheFolder() const {
    std::string cacheFolderName = getModelCacheFolderPath(cacheDirectory);
    std::filesystem::create_directories(cacheFolderName);
}

void ZooManager::removeCacheFolder() const {
    std::string cacheFolderName = getModelCacheFolderPath(cacheDirectory);
    std::filesystem::remove_all(cacheFolderName);
}

bool ZooManager::isCached() const {
    return checkExists(getModelCacheFolderPath(cacheDirectory));
}

bool ZooManager::checkExists(const std::string& path) const {
    return std::filesystem::exists(path);
}

void ZooManager::downloadModel() {
    // Setup download url
    const std::string modelUrl = "http://mlcloud-services-load-balancer.default.stg.easyml/models/api/v1/models/download";
    cpr::Url url = cpr::Url{modelUrl};

    // Setup header
    cpr::Header header;
    header.insert({"x-team-id", "ecc1ccd9-daa6-45d0-a4c7-81fb11b4b0b9"});

    // Setup HTTP request parameters
    cpr::Parameters parameters;
    parameters.AddParameter(cpr::Parameter("model_slug", modelDescription.getModelSlug()));
    parameters.AddParameter(cpr::Parameter("platform", modelDescription.getPlatform()));

    // Add optional parameters
    std::string modelInstanceSlug = modelDescription.getModelInstanceSlug();
    if(modelInstanceSlug.size() > 0) {
        parameters.AddParameter(cpr::Parameter("model_instance_slug", modelInstanceSlug));
    }

    // Send HTTP request
    cpr::Response response = cpr::Get(url, header, parameters);
    if(response.status_code != cpr::status::HTTP_OK) {
        // Cleanup cache folder
        removeCacheFolder();

        // Inform the user about the error and print out model description
        // for easier debugging
        std::string errorMessage = "Failed to download model\n" + modelDescription.toString();

        throw std::runtime_error(errorMessage);
    }

    // Unpack model download link - slice off first and last two characters
    // The returned text is in the format: ["link"]
    std::string link = response.text.substr(2, response.text.size() - 2 - 2);

    // Download model
    cpr::Url downloadUrl = cpr::Url{link};
    cpr::Response downloadResponse = cpr::Get(downloadUrl);

    // Save to tar file
    std::string folder = getModelCacheFolderPath(cacheDirectory);
    std::string tarPath = combinePaths(folder, "model.tar.xz");
    std::ofstream outStream(tarPath, std::ios::binary);
    outStream.write(downloadResponse.text.c_str(), downloadResponse.text.size());
    outStream.close();
}

NNArchive ZooManager::loadModelFromCache() const {
    const std::string cacheFolder = getModelCacheFolderPath(cacheDirectory);
    const std::string zippedModelPath = combinePaths(cacheFolder, "model.tar.xz");

    // Make sure the zipped model exists
    if(!checkExists(zippedModelPath)) {
        std::string errorMessage = "Zipped model " + zippedModelPath + " not found in cache.";
        throw std::runtime_error(errorMessage);
    }

    // NNArchive only accepts depthai's Path type
    const Path depthaiPath(zippedModelPath);
    return NNArchive(depthaiPath);
}

NNArchive getModelFromZoo(const NNModelDescription& modelDescription, const std::string& cacheDirectory, bool useCached, bool cacheModel) {
    // Initialize ZooManager
    ZooManager zooManager(modelDescription, cacheDirectory);

    // Check if model is cached
    bool modelIsCached = zooManager.isCached();
    bool useCachedModel = useCached && modelIsCached;

    // Use cached model if present and useCached is true
    if(useCachedModel) {
        auto archive = zooManager.loadModelFromCache();
        return archive;
    }

    // Remove cached model if present
    if(modelIsCached) {
        zooManager.removeCacheFolder();
    }

    // Create cache folder
    zooManager.createCacheFolder();

    // Download model
    zooManager.downloadModel();

    // Load model from cache
    NNArchive archive = zooManager.loadModelFromCache();

    // Remove cache folder if cacheModel is false and the model was not cached prior to downloading it
    if(!cacheModel && !modelIsCached) {
        zooManager.removeCacheFolder();
    }

    return archive;
}

void downloadModelsFromZoo(const std::string& path, const std::string& cacheDirectory, bool verbose) {
    // Make sure 'path' exists
    if(!std::filesystem::exists(path)) throw std::runtime_error("Path does not exist: " + path);

    // Find all yaml files in 'path'
    std::vector<std::string> yamlFiles;
    for(const auto& entry : std::filesystem::directory_iterator(path)) {
        std::string filePath = entry.path().string();
        if(utility::isYamlFile(filePath)) {
            yamlFiles.push_back(filePath);
        }
    }

    // Download models from yaml files
    for(size_t i = 0; i < yamlFiles.size(); ++i) {
        // Parse yaml file
        const std::string& yamlFile = yamlFiles[i];
        auto modelDescription = NNModelDescription::fromYaml(yamlFile);

        // Download model - ignore the returned NNArchive here, as we are only interested in downloading the model
        bool errorOccurred = false;
        try {
            getModelFromZoo(modelDescription, cacheDirectory, false);
        } catch(const std::exception& e) {
            std::cerr << "Failed to download model [" << i + 1 << "/" << yamlFiles.size() << "]:\n" << e.what() << std::endl;
            errorOccurred = true;
        }

        // Print verbose output
        if(verbose && !errorOccurred) {
            std::cout << "Downloaded model [" << i + 1 << "/" << yamlFile.size() << "]:\n" << modelDescription << std::endl;
        }
    }
}

}  // namespace dai