#ifndef __SCENE_H_
#define __SCENE_H_
#include <unordered_map>
#include "utils/HashedString.hpp"
#include "gamebasis/ComponentManager.hpp"

namespace DeNgine
{

using Actor = unsigned int;
class Scene
{
    std::unordered_map<utils::HashedString, IComponentManager&> m_CMmap;
public:
    const std::unordered_map<utils::HashedString, IComponentManager&>&
    getComponentManagersMap() const { return m_CMmap; }
};
}
#endif
