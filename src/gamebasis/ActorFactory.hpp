#pragma once
#include "gamebasis/Scene.hpp"

namespace DeNgine
{
class ActorFactory
{
    ActorFactory() = default;
    ActorFactory(ActorFactory&) = delete;
    void operator=(const ActorFactory&) = delete;

    Actor m_next;

public:
    Actor getNext()
    {
        return m_next++;
    }

    Actor loadFromXML(const Scene& scene, const tinyxml2::XMLElement* root);
    static ActorFactory& getInstance()
    {
        static ActorFactory instance;
        return instance;
    }
};

}
