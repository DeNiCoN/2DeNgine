#include "gamebasis/TransformComponentManager.hpp"
#include "utils/XMLUtils.hpp"

namespace DeNgine
{

bool TransformCM::VLoadComponent(Actor p_actor, const tinyxml2::XMLElement *p_root)
{
    auto position = p_root->FirstChildElement("Position");
    auto velocity = p_root->FirstChildElement("Velocity");
    float angle = p_root->FloatAttribute("angle");

    Transform transform;
    if (position)
    {
        transform.position = utils::asVec3(position);
    }

    if (velocity)
    {
        transform.velocity = utils::asVec2(velocity);
    }
    transform.angle = angle;
    add(p_actor, transform);
    return true;
}

}
