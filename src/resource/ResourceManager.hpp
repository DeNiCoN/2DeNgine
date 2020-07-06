#pragma once
#include <functional>
#include <vector>
#include <memory>
#include <cassert>
#include "utils/LRUCache.hpp"
#include "utils/HashedString.hpp"

namespace DeNgine {

using Resource = utils::HashedString;

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
};
}
