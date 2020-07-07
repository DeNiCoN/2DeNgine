#pragma once
#include <glm/mat4x4.hpp>
#include "gamebasis/ComponentManager.hpp"
#include "gamebasis/Scene.hpp"
#include "render/SpriteBatch.hpp"
#include "utils/HashedString.hpp"

namespace DeNgine
{

using SpriteMap = std::unordered_map<Actor, Sprite>;
class SpriteCM final : public IComponentManager
{
    SpriteBatch m_batch;
public:
    SpriteMap m_sprites;
    void add(Actor actor)
    {
        m_sprites[actor];
    }
    SpriteCM(const RenderManager& p_renderManager)
        : m_batch(p_renderManager) {}
    inline const utils::HashedString VName() const override
    { return "SpriteCM"; }

    bool VLoadComponent(Actor, const tinyxml2::XMLElement*) override
    { return false; }

    void VOnAddedTo(Scene&) override;
};
}
