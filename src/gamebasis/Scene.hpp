#pragma once
#include <cassert>
#include <functional>
#include <memory>
#include <unordered_map>
#include <glm/mat4x4.hpp>
#include "utils/HashedString.hpp"
#include "gamebasis/ComponentManager.hpp"

namespace DeNgine
{

enum class ViewportType
{
SCREEN
};

class SceneFactory;
class RenderManager;

using Actor = unsigned int;
class Scene
{
    friend class SceneFactory;
    friend class RenderManager;

    glm::mat4 m_projection = glm::mat4(1.f);
    glm::mat4 m_view = glm::mat4(1.f);
    std::vector<std::function<void(double)>> m_toUpdate;
    std::vector<std::function<void()>> m_toPostUpdate;
    std::vector<std::function<void(double)>> m_toRender;
    std::unordered_map<utils::HashedString, IComponentManagerPtr> m_CMmap;
    ViewportType m_viewportType;
public:
    glm::mat4& projection() { return m_projection; }
    glm::mat4& view() { return m_view; }

    const std::unordered_map<utils::HashedString, IComponentManagerPtr>&
    getComponentManagersMap() const { return m_CMmap; }

    void postUpdate()
    {
        //Something predefined

        //ToUpdate
        for (auto f : m_toPostUpdate)
            f();
    }

    void update(double delta)
    {
        //Something predefined

        //ToUpdate
        for (auto f : m_toUpdate)
            f(delta);
    }

    void render(double delta)
    {
        //Something predefined

        //ToUpdate
        for (auto f : m_toRender)
            f(delta);
    }

    void addToPostUpdate(std::function<void()> t_func) {
        m_toPostUpdate.push_back(t_func);
    }

    void addToUpdate(std::function<void(double)> t_func) {
        m_toUpdate.push_back(t_func);
    }

    void addToRender(std::function<void(double)> t_func) {
        m_toRender.push_back(t_func);
    }

    /*void removeFromUpdate(const std::function<void(double)> t_func)
    {
        //TODO Do something with this
        //auto f = std::find(m_toUpdate.begin(), m_toUpdate.end(), t_func);
        //assert(f != m_toUpdate.end() && "There is no that function in ToUpdate");
        //m_toUpdate.erase(f);
    }********/

    void addComponentManager(IComponentManagerPtr t_comp)
    {
        m_CMmap.insert({t_comp->VName(), t_comp});
        t_comp->VOnAddedTo(*this);
    }
};

using ScenePtr = std::shared_ptr<Scene>;
}
