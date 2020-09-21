#pragma once
#include <memory>
#include <vector>

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
    virtual const utils::HashedString VName() const = 0;
    virtual ~IComponentManager() = default;
    virtual bool VLoadComponent(Actor, const tinyxml2::XMLElement*) = 0;
    virtual void VOnAddedTo(Scene&) = 0;
    virtual void VInit(Scene&) {};
    virtual std::vector<utils::HashedString> requireList() { return {}; }
};

using IComponentManagerPtr = std::shared_ptr<IComponentManager>;
}
