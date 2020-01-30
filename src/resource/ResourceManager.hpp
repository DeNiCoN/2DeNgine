#ifndef __RESOURCE_MANAGER_H_
#define __RESOURCE_MANAGER_H_
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

};

class ResourceHandle
{
    friend class ResourceManager;
private:
    struct _private_ { explicit _private_() = default; };
public:
    ResourceHandle(_private_, const Resource& t_res,
                   std::unique_ptr<ResourceHandleData> t_data)
        :data(std::move(t_data)), resource(t_res) {}
    const std::unique_ptr<ResourceHandleData> data;
    const Resource resource;
};

class IResourceLoader
{
public:
    virtual ~IResourceLoader() = default;
    virtual ResourceHandleData& VLoad(char* raw_buffer, std::size_t t_rSize,
                                     char* buffer) = 0;
    virtual std::size_t VGetSize(const char* raw_buffer,
                                 std::size_t t_rSize) const = 0;
    virtual std::initializer_list<const char*> VGetExtensions() = 0;
};

class IFileSystem
{
public:
    virtual ~IFileSystem() = default;
    virtual bool VExists(const Resource& t_resource) const = 0;
    virtual bool VGetSize(const Resource& t_resource) = 0;
    //Load raw data into memory.
    virtual void VLoadIntoMemory(const Resource& t_resource, char* buffer) = 0;
};

class ResourceManager
{
    LRUCache<Resource, ResourceHandlePtr> m_cache;
    std::vector<IFileSystem> m_filesystems;

public:
    ResourceManager(unsigned int sizeMB);

    //Return pointer to loaded into memory file
    //memory is null terminated
    std::unique_ptr<char[]> loadToMemory(const Resource& t_resource,
                                        std::size_t* t_size,
                                        IFileSystem* t_custom = nullptr);

    //Return handle if already been loaded
    //else return null
    ResourceHandlePtr getHandle(const Resource& t_resource);
    ResourceHandlePtr newHandle(const Resource& t_resource,
                                const std::unique_ptr<ResourceHandleData> data);
};
}
#endif
