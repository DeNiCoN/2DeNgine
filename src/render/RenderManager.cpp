#include "render/RenderManager.hpp"
#include <easylogging++.h>

namespace DeNgine
{

bool RenderManager::initialize()
{
    if(!m_wManager.createWindow())
    {
        return false;
    }
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
