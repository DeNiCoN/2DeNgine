#pragma once
#include <functional>
#include <vector>
#include <memory>
#include <cassert>
#include "utils/LRUCache.hpp"
#include "utils/HashedString.hpp"

namespace DeNgine {

class ResourceHandle;
class ResourceManager;

using Resource = utils::HashedString;
using ResourceHandlePtr = std::shared_ptr<ResourceHandle>;

class ResourceHandleData
{
public:
    virtual ~ResourceHandleData() = default;
};

class ResourceHandle
{
    friend class ResourceManager;
private:
    struct _private_ { explicit _private_() = default; };
public:
    ResourceHandle(_private_, const Resource& p_res,
                   std::unique_ptr<ResourceHandleData> p_data)
        :data(std::move(p_data)), resource(p_res) {}
    const std::unique_ptr<const ResourceHandleData> data;
    const Resource resource;
};

class IResourceLoader
{
public:
    virtual ~IResourceLoader() = default;
    //virtual ResourceHandleData& VLoad(char* raw_buffer, std::size_t p_rSize,
    //                                 char* buffer) = 0;
    //virtual std::size_t VGetSize(const char* raw_buffer,
    //                             std::size_t p_rSize) const = 0;
    //virtual std::initializer_list<const char*> VGetExtensions() = 0;
};

class IFileSystem
{
public:
    virtual ~IFileSystem() = default;
    virtual bool VExists(const Resource& p_resource) const = 0;
    virtual std::size_t VGetSize(const Resource& p_resource) = 0;
    //Load raw data into memory.
    virtual void VLoadIntoMemory(const Resource& p_resource, char* buffer) = 0;
};

class ResourceManager
{
    LRUCache<Resource, ResourceHandlePtr> m_cache;
    std::vector<IFileSystem*> m_filesystems;

public:
    //Return pointer to loaded into memory file
    //memory is null terminated
    std::unique_ptr<char[]> loadToMemory(const Resource& resource,
                                         bool null_terminate = false,
                                         std::size_t* size = nullptr,
                                         IFileSystem* custom = nullptr);

    inline void addFilesystem(IFileSystem& p_fs)
    {
        m_filesystems.push_back(&p_fs);
    }

    //Return handle if already been loaded
    //else return null
    ResourceHandlePtr getHandle(const Resource& p_resource);
    ResourceHandlePtr newHandle(const Resource& p_resource,
                                const std::unique_ptr<ResourceHandleData> data);
};
}
