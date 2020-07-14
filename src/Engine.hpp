#pragma once
#include <vector>
#include "render/RenderManager.hpp"
#include "gamebasis/Scene.hpp"
#include "gamebasis/ActorFactory.hpp"
#include "easylogging++.h"

#define ELPP_FEATURE_CRASH_LOG

INITIALIZE_EASYLOGGINGPP

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
    ResourceManager m_resourceManager;
    RenderManager m_renderManager {m_windowManager, scenes, m_resourceManager};
    ActorFactory m_actorFactory;

    std::vector<ScenePtr> scenes;

    bool init();
    bool shouldClose();
public:
    const double SPF = 1.0/60.0;

    const RenderManager& getRenderer() const { return m_renderManager; }

    bool run(ScenePtr initial);
};
}


