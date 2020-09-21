#pragma once
#include <tinyxml2.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace DeNgine
{
namespace utils
{

inline glm::vec2 asVec2(const tinyxml2::XMLElement *p_root)
{
    return {p_root.FloatAttribute("x"), p_root.FloatAttribute("y")};
}

inline glm::vec3 asVec3(const tinyxml2::XMLElement *p_root)
{
    return { p_root.FloatAttribute("x"),
    p_root.FloatAttribute("y"),
    p_root.FloatAttribute("z")};
}

inline glm::vec4 asVec4(const tinyxml2::XMLElement *p_root)
{
    return { p_root.FloatAttribute("x"),
    p_root.FloatAttribute("y"),
    p_root.FloatAttribute("z"),
    p_root->FloatAttribute("w")};
}

}
}
