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
    bool dirty = true;
};

using TransformMap = std::unordered_map<Actor, Transform>;
class TransformCM final : public IComponentManager
{
    TransformMap m_transforms;
public:

    const utils::HashedString VName() const override
    { return "TransformCM"; }

    bool VLoadComponent(Actor p_actor, const tinyxml2::XMLElement* p_root) override;
   
    void VOnAddedTo(Scene& p_scene) override
    {
        p_scene.addToPostUpdate([&]()
        {
            //TODO dirty bit
            for (auto& [actor, transform] : m_transforms)
            {
                transform.dirty = false;
            }
        });
    }

    void add(Actor p_actor, const Transform& p_initial = {})
    {
        m_transforms[p_actor] = p_initial;
    }

    bool contains(Actor p_actor)
    {
        return m_transforms.count(p_actor);
    }

    void changeVelocity(Actor p_actor, glm::vec2 p_vel)
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

    inline const Transform& get(Actor p_actor) const
    { return m_transforms.at(p_actor); }

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
