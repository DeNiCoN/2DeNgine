#pragma once
#include "gamebasis/Scene.hpp"
#include "gamebasis/ComponentManagerFactory.hpp"
#include "resource/XMLResourceLoader.hpp"

namespace DeNgine
{

class ActorFactory;

class SceneFactory
{
    ActorFactory& m_actorFactory;
    const XMLResourceLoader& m_xmlLoader;
    const ComponentManagerFactory& m_CMFactory;
public:
    SceneFactory(ActorFactory& p_actorFactory, const XMLResourceLoader& p_xmlLoader,
                 ComponentManagerFactory& p_CMFactory)
        : m_actorFactory(p_actorFactory), m_xmlLoader(p_xmlLoader),
          m_CMFactory(p_CMFactory)
    {}
    SceneFactory(SceneFactory&) = delete;
    void operator=(const SceneFactory&) = delete;

    ScenePtr loadFromXML(const tinyxml2::XMLElement* root);
};

}
