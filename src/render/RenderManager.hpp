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
private:

    ShaderResourceLoader m_shaderLoader;
    WindowManager& m_wManager;
    std::vector<Scene>& m_scenes;
public:
    bool initialize();
    void terminate();

    RenderManager(WindowManager& p_window, std::vector<Scene>& p_scenes,
                  ResourceManager& m_resourceManager) :
        m_shaderLoader(m_resourceManager),
        m_wManager(p_window),
        m_scenes(p_scenes)
    {}

    const ShaderResourceLoader& getShaderLoader() const {return m_shaderLoader; }

    inline void render(double fromUpdate)
    {
        //TODO normal per scene framebuffer rendering
        glClearColor(0.1, 0.1, 0.5, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        for(auto scene : m_scenes)
            scene.render(fromUpdate);

        m_wManager.swapBuffers();
    }

};

}
