#pragma once
#include <glm/mat4x4.hpp>
#include "gamebasis/ComponentManager.hpp"
#include "gamebasis/Scene.hpp"
#include "utils/HashedString.hpp"

namespace DeNgine
{
struct Sprite
{
    //TODO texture
    //
    glm::mat4 model;
};

using SpriteMap = std::unordered_map<Actor, Sprite>;
class SpriteCM final : public IComponentManager
{
    inline const utils::HashedString VName() const override
    { return "SpriteCM"; }

    bool VLoadComponent(Actor, const tinyxml2::XMLElement*) override
    { return true; }

    void VOnAddedTo(Scene&) override;
};
}
