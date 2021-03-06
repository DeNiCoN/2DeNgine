#pragma once
#include <vector>
#include <glm/mat3x3.hpp>
#include <glad/glad.h>
#include "render/WindowManager.hpp"
#include "resource/ShaderResourceLoader.hpp"
#include "gamebasis/Scene.hpp"

namespace DeNgine
{

class RenderManager
{
    ShaderResourceLoader m_shaderLoader;
    WindowManager& m_wManager;
    std::vector<ScenePtr>& m_scenes;
    ViewportType m_viewportType;
public:
    bool initialize();
    void terminate();

    RenderManager(WindowManager&, std::vector<ScenePtr>&, ResourceManager&);

    const ShaderResourceLoader& getShaderLoader() const {return m_shaderLoader; }

    void render(double fromUpdate)
    {
        //TODO framebuffer rendering
        glClearColor(0.1, 0.1, 0.5, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        for(auto scene : m_scenes)
            scene->render(fromUpdate);

        m_wManager.swapBuffers();
    }

};

}
