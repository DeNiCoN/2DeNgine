#pragma once
#include "ComponentManagerFactory.hpp"
#include "gamebasis/Scene.hpp"

namespace DeNgine
{
class ActorFactory
{
    Actor m_next;
public:
    ActorFactory()
    {}
    ActorFactory(ActorFactory&) = delete;
    void operator=(const ActorFactory&) = delete;
    Actor getNext()
    {
        return m_next++;
    }

    Actor loadFromXML(Scene& scene, const tinyxml2::XMLElement* root);
};

}
