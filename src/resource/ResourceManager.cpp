#include "resource/ResourceManager.hpp"
#include "easylogging++.h"
#include "string.h"
#include <iostream>
#include <algorithm>

namespace DeNgine
{

std::unique_ptr<char[]> ResourceManager::loadToMemory(
    const Resource& t_resource,
    bool p_nullTerm,
    std::size_t* t_size, IFileSystem* t_custom) const
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
            LOG(ERROR) << "Custom file system for resource " << t_resource.str <<
                " not found";
            return nullptr;
        }
        filesystem = t_custom;
    }
    else
    {
        auto filesystem_it = std::find_if(m_filesystems.begin(), m_filesystems.end(),
        [&](const auto e)
        {
            return e->VExists(t_resource);
        });
        if (filesystem_it == m_filesystems.end())
        {
            LOG(ERROR) << "File system for resource " << t_resource.str <<
                " not found";
            return nullptr;
        }
        filesystem = filesystem_it->get();
    }
    //Load resource from memory
    //
    //Why +1?
    //Null termination
    //cleverness vs readability?
    //is it readable?
    std::size_t size = filesystem->VGetSize(t_resource) + p_nullTerm;
    auto raw_buffer = std::make_unique<char[]>(size);
    if (p_nullTerm)
        raw_buffer[size - 1] = '\0';
    if (t_size)
        *t_size = size;
    filesystem->VLoadIntoMemory(t_resource, raw_buffer.get());
    return raw_buffer;
}
}
