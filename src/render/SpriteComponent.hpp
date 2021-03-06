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
    void add(Actor actor, glm::vec4 initialColor = {})
    {
        m_sprites[actor].color = initialColor;
    }
    SpriteCM(const RenderManager& p_renderManager)
        : m_batch(p_renderManager) {}
    inline const utils::HashedString VName() const override
    { return "SpriteCM"; }

    bool VLoadComponent(Actor, const tinyxml2::XMLElement*) override;

    void VOnAddedTo(Scene&) override;
};
}
