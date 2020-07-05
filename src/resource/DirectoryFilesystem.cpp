#include "resource/DirectoryFilesystem.hpp"
#include <fstream>

namespace DeNgine
{

namespace fs = std::filesystem;

DirectoryFilesystem::DirectoryFilesystem(std::filesystem::path p_path)
{
    for(auto& p: fs::recursive_directory_iterator(p_path))
        if (!p.is_directory())
            //TODO very likely that there is bug, because HashedString uses
            //const char* and do not do dynamic allocation
            m_file_map[p.path().string().c_str()] = fs::file_size(p);
}

void DirectoryFilesystem::VLoadIntoMemory(const Resource &p_resource, char *buffer)
{
    std::ifstream file;
    file.open(p_resource.str, std::ifstream::in | std::ifstream::binary);
    assert(!file.fail() && "Failded to open file");
    file.read(buffer, VGetSize(p_resource));
}

}
