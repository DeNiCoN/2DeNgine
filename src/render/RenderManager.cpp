#include "render/RenderManager.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <easylogging++.h>

namespace DeNgine
{

RenderManager::RenderManager(WindowManager& p_window,
                             std::vector<ScenePtr>& p_scenes,
                             ResourceManager& m_resourceManager)
    : m_shaderLoader(m_resourceManager),
      m_wManager(p_window),
      m_scenes(p_scenes)
{
}

bool RenderManager::initialize()
{
    if(!m_wManager.createWindow())
    {
        return false;
    }
    m_wManager.registerOnResize([&](unsigned w, unsigned h)
    {
        if (m_viewportType == ViewportType::SCREEN)
        {
            glViewport(0, 0, w, h);
        }

        for (auto scenePtr : m_scenes)
        {
            if(scenePtr->m_viewportType == ViewportType::SCREEN)
            {
                scenePtr->projection() = glm::ortho(-w/2.f, w/2.f, -h/2.f, h/2.f);
            }
        }
    });
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        LOG(FATAL) << "Failed to initialize GLAD";
        return false;
    }
    return true;
}
void RenderManager::terminate()
{
    m_wManager.deleteWindow();
}

}
