#include "resource/ResourceManager.hpp"
#include "string.h"
#include <iostream>
#include <algorithm>

namespace DeNgine
{

std::unique_ptr<char[]> ResourceManager::loadToMemory(const Resource& t_resource,
                                    std::size_t* t_size, IFileSystem* t_custom)
{
    //Load into memory and pass it to loader
    //Find file system or use custom
    //Actually file system idea is crazy, for example i can write filesystem
    //that downloads through network or zip file filesystem
    //TODO I think i need to find better name for filesystem
    IFileSystem* filesystem;
    if (t_custom)
    {
        if (t_custom->VExists(t_resource))
        {
            std::cout << "Resource " << t_resource.str << " is not in custom"
                      << "filesystem\n";
            return nullptr;
        }
        filesystem = t_custom;
    }
    else
    {
        auto filesystem_it = std::find_if(m_filesystems.begin(), m_filesystems.end(),
        [&](const auto& e)
        {
            return e.VExists(t_resource);
        });

        if (filesystem_it == m_filesystems.end())
        {
            std::cout << "File system for resource " << t_resource.str <<
                " not found";
            return nullptr;
        }
        filesystem = &(*filesystem_it);
    }
    //Load resource from memory
    std::size_t size = filesystem->VGetSize(t_resource) + 1;
    auto raw_buffer = std::make_unique<char[]>(size);
    if (t_size)
        *t_size = size;
    filesystem->VLoadIntoMemory(t_resource, raw_buffer.get());
    return std::move(raw_buffer);
}

ResourceHandlePtr ResourceManager::getHandle(const Resource &t_resource)
{
    auto it = m_cache.find(t_resource);
    if (it != m_cache.end())
    {
        return it->second;
    }
    else
    {
        return ResourceHandlePtr(nullptr);
    }
}

ResourceHandlePtr ResourceManager::newHandle(const Resource& t_resource,
                                std::unique_ptr<ResourceHandleData> t_data)
{
    ResourceHandlePtr handle =
        std::make_shared<ResourceHandle>(ResourceHandle::_private_(),
                                         t_resource, std::move(t_data));
    m_cache.insert(t_resource, handle);
    return handle;
}
}
