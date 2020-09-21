#include "render/SpriteComponent.hpp"
#include "resource/ShaderResourceLoader.hpp"
#include "gamebasis/TransformComponentManager.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "utils/XMLUtils.hpp"
#include <tinyxml2.h>

namespace DeNgine
{

void updateSprite(Sprite& p_sprite, const Transform& p_transform)
{
    p_sprite.world =
        glm::translate(
            glm::rotate(glm::mat4(1.f),
                        p_transform.angle, glm::vec3(0.f, 0.f, 1.f)),
            p_transform.position);
}

void SpriteCM::VOnAddedTo(Scene& p_scene)
{
    m_batch.projection() = p_scene.projection();
    p_scene.addToUpdate([&](double delta)
    {
        //TODO Update
        for (auto& [actor, sprite] : m_sprites)
        {
            if (p_scene.getComponentManagersMap().count("TransformCM"))
            {
                TransformCM& transCM =
                    static_cast<TransformCM&>(
                        p_scene.getComponentManagersMap().at("TransformCM"));
                if (transCM.contains(actor))
                {
                    auto& transform = transCM.get(actor);
                    if (transform.dirty)
                    {
                        updateSprite(sprite, transform);
                    }
                }
            }
        }
    });

    p_scene.addToRender([&](double delay)
    {
        //FIXME Rendering
        for (auto& [actor, sprite] : m_sprites)
        {
            m_batch.drawOne(p_scene.projection(), p_scene.view(), sprite);
        }
    });
}

bool SpriteCM::VLoadComponent(Actor p_actor, const tinyxml2::XMLElement *p_root)
{
    auto colorElem = p_root->FirstChildElement("Color");
    if (colorElem)
    {
        add(p_actor, utils::asVec4(colorElem));
        return true;
    }
    add(p_actor);
    return true;
}
}
