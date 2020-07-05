#pragma once
#include "gamebasis/Scene.hpp"
#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "gamebasis/ComponentManager.hpp"
#include "utils/HashedString.hpp"

namespace DeNgine
{

struct Transform
{
    glm::vec3 position;
    glm::vec2 velocity;
    float angle;
    bool dirty;
};

using TransformMap = std::unordered_map<Actor, Transform>;
class TransformCM final : public IComponentManager
{
    TransformMap m_transforms;
public:

    const utils::HashedString VName() const override
    { return "TransformCM"; }

    bool VLoadComponent(Actor, const tinyxml2::XMLElement*) override
    { return true; }

    void VOnAddedTo(Scene& p_scene) override
    {
        p_scene.addToPostUpdate([]()
        {
            //TODO dirty bit
        });
    }

    inline const Transform& add(Actor p_actor)
    {
        return (*m_transforms.insert(std::pair(p_actor, Transform())).first).second;
    }

    inline bool contains(Actor p_actor)
    {
        return m_transforms.count(p_actor);
    }

    inline void changeVelocity(Actor p_actor, glm::vec2 p_vel)
    {
        auto& t = m_transforms.at(p_actor);
        t.velocity = p_vel;
        t.dirty = true;
    }

    inline void changePosition(Actor p_actor, glm::vec3 p_position)
    {
        auto& t = m_transforms.at(p_actor);
        t.position = p_position;
        t.dirty = true;
    }

    inline void changeAngle(Actor p_actor, float p_angle)
    {
        auto& t = m_transforms.at(p_actor);
        t.angle = p_angle;
        t.dirty = true;
    }

    inline void change(Actor p_actor, glm::vec3 p_position,
                       glm::vec2 p_vel, float p_angle)
    {
        auto& t = m_transforms.at(p_actor);
        t.position = p_position;
        t.velocity = p_vel;
        t.angle = p_angle;
        t.dirty = true;
    }
};
}
