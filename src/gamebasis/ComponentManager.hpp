#ifndef __COMPONENTMANAGER_H_
#define __COMPONENTMANAGER_H_

namespace tinyxml2 {
class XMLElement;
}

namespace DeNgine
{

namespace utils {
class HashedString;
}

using Actor = unsigned int;

class IComponentManager
{
public:
    virtual utils::HashedString& VName() = 0;
    virtual ~IComponentManager() = default;
    virtual bool VLoadComponent(Actor, const tinyxml2::XMLElement*);
};
}
#endif
