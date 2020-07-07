#pragma once
#include <cassert>
#include <functional>
#include <unordered_map>
#include <glm/mat4x4.hpp>
#include "utils/HashedString.hpp"
#include "gamebasis/ComponentManager.hpp"

namespace DeNgine
{

using Actor = unsigned int;
class Scene
{
    glm::mat4 m_projection = glm::mat4(1.f);
    glm::mat4 m_view = glm::mat4(1.f);
    std::vector<std::function<void(double)>> m_toUpdate;
    std::vector<std::function<void()>> m_toPostUpdate;
    std::vector<std::function<void(double)>> m_toRender;
    std::unordered_map<utils::HashedString, IComponentManager&> m_CMmap;
public:
    glm::mat4& projection() { return m_projection; }
    glm::mat4& view() { return m_view; }

    const std::unordered_map<utils::HashedString, IComponentManager&>&
    getComponentManagersMap() const { return m_CMmap; }

    inline void postUpdate()
    {
        //Something predefined

        //ToUpdate
        for (auto f : m_toPostUpdate)
            f();
    }

    inline void update(double delta)
    {
        //Something predefined

        //ToUpdate
        for (auto f : m_toUpdate)
            f(delta);
    }

    inline void render(double delta)
    {
        //Something predefined

        //ToUpdate
        for (auto f : m_toRender)
            f(delta);
    }

    inline void addToPostUpdate(std::function<void()> t_func) {
        m_toPostUpdate.push_back(t_func);
    }

    inline void addToUpdate(std::function<void(double)> t_func) {
        m_toUpdate.push_back(t_func);
    }

    inline void addToRender(std::function<void(double)> t_func) {
        m_toRender.push_back(t_func);
    }

    /*void removeFromUpdate(const std::function<void(double)> t_func)
    {
        //TODO Do something with this
        //auto f = std::find(m_toUpdate.begin(), m_toUpdate.end(), t_func);
        //assert(f != m_toUpdate.end() && "There is no that function in ToUpdate");
        //m_toUpdate.erase(f);
    }********/

    inline void addComponentManager(IComponentManager& t_comp)
    {
        m_CMmap.insert({t_comp.VName(), t_comp});
        t_comp.VOnAddedTo(*this);
    }
};
}
