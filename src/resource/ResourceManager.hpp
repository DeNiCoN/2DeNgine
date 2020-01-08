#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include "utils/HashedString.hpp"

namespace DeNgine {
struct Resource : public utils::HashedString
{
    const unsigned int separatorPos;
    static const char separator = '|';
    constexpr Resource(const char* t_name)
        :HashedString(t_name),
         separatorPos(t_name - std::char_traits<char>::find(t_name, length, separator))
    {
        assert(std::char_traits<char>::find(t_name, length, separator) &&
               "No separator in resource name");
    }
};

class ResourceHandle
{

public:
    ResourceHandle();
};

using ResourceHandlePtr = std::shared_ptr<ResourceHandle>;

class ResourceManager
{

public:
    ResourceManager(unsigned int sizeMB);

    //Check if resource is loaded then return it, else check is
    //is resource loader present, is resource file loaded
    ResourceHandlePtr getHandle(const Resource& t_resource);



};
}
