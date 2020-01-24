#ifndef __RESOURCE_MANAGER_H_
#define __RESOURCE_MANAGER_H_
#include <vector>
#include <memory>
#include <cassert>
#include "utils/HashedString.hpp"

namespace DeNgine {

class ResourceHandle;

using Resource = utils::HashedString;
using ResourceHandlePtr = std::shared_ptr<ResourceHandle>;

class ResourceHandleData
{

};

class ResourceHandle
{
    ResourceHandleData& m_data;
public:
    const Resource resource;
    ResourceHandle(Resource& t_res);
};

class ResourceLoader
{
    virtual ResourceHandleData VLoad(Resource& t_res) = 0;

};

class ResourceManager
{
    std::vector<ResourceHandlePtr> m_LRUList;

public:
    ResourceManager(unsigned int sizeMB);

    //Check if resource is loaded then return it, else check is
    //is resource loader present, is resource file loaded
    ResourceHandlePtr getHandle(const Resource& t_resource);
};
}
#endif
