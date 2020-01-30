#ifndef __SCENE_H_
#define __SCENE_H_
#include <cassert>
#include <functional>
#include <unordered_map>
#include "utils/HashedString.hpp"
#include "gamebasis/ComponentManager.hpp"

namespace DeNgine
{

using Actor = unsigned int;
class Scene
{
    std::vector<std::function<void(double)>> m_toUpdate;
    std::unordered_map<utils::HashedString, IComponentManager&> m_CMmap;
public:
    const std::unordered_map<utils::HashedString, IComponentManager&>&

    getComponentManagersMap() const { return m_CMmap; }

    inline void update(double delta)
    {
        //Something predefined

        //ToUpdate
        for (auto f : m_toUpdate)
            f(delta);
    }

    void addToUpdate(std::function<void(double)> t_func) {
        m_toUpdate.push_back(t_func);
    }

    void removeFromUpdate(std::function<void(double)> t_func)
    {
        auto f = std::find(m_toUpdate.begin(), m_toUpdate.end(), t_func);
        assert(f != m_toUpdate.end() && "There is no that function in ToUpdate");
        m_toUpdate.erase(f);
    }

    void addComponentManager(IComponentManager& t_comp)
    {
        m_CMmap[t_comp.VName()] = t_comp;
        t_comp.VOnAddedTo(*this);
    }
};
}
#endif
