#pragma once
#include "render/WindowManager.hpp"

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

public:
    template<typename App>
    bool shouldClose()
    {
        //TODO app should close
        return m_windowManager.shouldClose();
    }

    template<typename App>
    bool run(App& app)
    {
        //Initialize engine systems
        WindowManager::initialize();
        m_windowManager.createWindow();

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
            }
            //TODO render

            glfwPollEvents();
        }
        //TODO termination
        WindowManager::finalize();
        return 0;

    }
};
}


