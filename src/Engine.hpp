#pragma once
#include <vector>
#include "render/RenderManager.hpp"
#include "gamebasis/Scene.hpp"
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
    RenderManager m_renderManager {m_windowManager, scenes, m_resourceManager};

public:
    ::std::vector<Scene> scenes;
    ResourceManager m_resourceManager;

    const RenderManager& getRenderer() const { return m_renderManager; }


    template<typename App>
    bool shouldClose()
    {
        //TODO app should close
        return m_windowManager.shouldClose();
    }

    bool init()
    {
        LOG(INFO) << "Engine initialization";
        //Initialize engine systems
        m_windowManager.initialize();
        m_renderManager.initialize();
        LOG(INFO) << "Engine initialization finished";
        return true;
    }

    template<typename App>
    bool run(App& app)
    {
        LOG(INFO) << "Engine run";
        //loop
        while (!shouldClose<App>())
        {
            m_currentTime = glfwGetTime();
            m_delta = m_currentTime - m_lastTime;
            m_lastTime = m_currentTime;
            m_delay += m_delta;
            while (m_delay >= 1)
            {
                m_delay -= 1;
                //TODO update
                for(auto scene : scenes)
                {
                    scene.update(m_delta);
                }
            }
            //TODO render
            m_renderManager.render(m_delay / 1.0);

            m_windowManager.poolEvents();
        }
        //TODO termination
        m_renderManager.terminate();
        m_windowManager.terminate();
        LOG(INFO) << "Engine finished successfully";
        return 0;
    }
};
}


