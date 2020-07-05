#pragma once
#include "resource/ResourceManager.hpp"
#include <filesystem>

namespace DeNgine
{

class DirectoryFilesystem final : public IFileSystem
{
    std::unordered_map<Resource, std::size_t> m_file_map;
public:
    DirectoryFilesystem(std::filesystem::path);
    bool VExists(const Resource& p_resource) const override
    {
        return m_file_map.count(p_resource);
    }
    std::size_t VGetSize(const Resource &p_resource) override
    {
        return m_file_map.at(p_resource);
    }
    void VLoadIntoMemory(const Resource& p_resource, char* buffer) override;
};

}
