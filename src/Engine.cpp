#include "Engine.hpp"

namespace DeNgine
{


bool Engine::shouldClose()
{
    //TODO app should close
    return m_windowManager.shouldClose();
}

bool Engine::init()
{
    LOG(INFO) << "Engine initialization";
    //Initialize engine systems
    m_windowManager.initialize();
    m_renderManager.initialize();
    LOG(INFO) << "Engine initialization finished";
    return true;
}

bool Engine::run(ScenePtr initial)
{
    LOG(INFO) << "Engine run";
    scenes.push_back(initial);
    //loop
    while (!shouldClose())
    {
        m_currentTime = glfwGetTime();
        m_delta = m_currentTime - m_lastTime;
        m_lastTime = m_currentTime;
        m_delay += m_delta;
        while (m_delay >= SPF)
        {
            m_delay -= SPF;
            //TODO update
            for(auto scene : scenes)
            {
                scene->update(m_delta);
            }
        }
        //TODO render
        m_renderManager.render(m_delay / SPF);

        m_windowManager.poolEvents();
    }
    //TODO termination
    m_renderManager.terminate();
    m_windowManager.terminate();
    LOG(INFO) << "Engine finished successfully";
    return 0;
}
}
