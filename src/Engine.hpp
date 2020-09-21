#pragma once
#include <vector>
#include "render/RenderManager.hpp"
#include "gamebasis/Scene.hpp"
#include "gamebasis/ActorFactory.hpp"
#include "gamebasis/SceneFactory.hpp"
#include "easylogging++.h"


#define ELPP_FEATURE_CRASH_LOG


namespace DeNgine
{

class Engine
{
private:
    double m_currentTime;
    double m_delta;
    double m_lastTime;
    double m_delay;
    WindowManager m_windowManager;
    RenderManager m_renderManager {m_windowManager, scenes, m_resourceManager};
    ActorFactory m_actorFactory;
    XMLResourceLoader m_xmlLoader {m_resourceManager};
    ComponentManagerFactory m_CMFactory;
    SceneFactory m_sceneFactory {m_actorFactory, m_xmlLoader, m_CMFactory};

    std::vector<ScenePtr> scenes;

    bool shouldClose();
    bool processConfigXML(const tinyxml2::XMLElement& config);
public:
    const double SPF = 1.0/60.0;

    const RenderManager& getRenderer() const { return m_renderManager; }

    ResourceManager m_resourceManager;
    bool init(const tinyxml2::XMLElement& config);
    bool run();
};
}


