#ifndef __COMPONENTMANAGER_H_
#define __COMPONENTMANAGER_H_

namespace tinyxml2 {
class XMLElement;
}

namespace DeNgine
{

class Scene;

namespace utils {
class HashedString;
}

using Actor = unsigned int;

class IComponentManager
{
public:
    virtual utils::HashedString& VName() const = 0;
    virtual ~IComponentManager() = default;
    virtual bool VLoadComponent(Actor, const tinyxml2::XMLElement*) = 0;
    virtual void VOnAddedTo(Scene&) = 0;
};
}
#endif
