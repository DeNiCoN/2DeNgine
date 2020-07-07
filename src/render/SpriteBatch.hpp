#pragma once
#include <resource/ShaderResourceLoader.hpp>
#include <render/RenderManager.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace DeNgine
{

struct Sprite
{
    glm::mat4 world;
    glm::vec4 color;
    //TODO texture
};

class SpriteBatch
{
    static void init();
    unsigned m_vao;
    unsigned m_colorBO;
    unsigned m_transformBO;
    float* m_transformBufferPtr;
    float* m_colorBufferPtr;
    static unsigned s_vbo;
    static bool s_initialized;

    unsigned m_capacity;
    unsigned m_numRendered;

    const RenderManager& m_rManager;
    ShaderProgramRHPtr m_shader;
    glm::mat4 m_projection;
    static constexpr float m_quadData[] { -1.f, 1.f,
            1.f, 1.f,
            1.f, -1.f,
            -1.f, 1.f,
            1.f, -1.f,
            -1.f, -1.f};
public:
    SpriteBatch(const RenderManager& rManager, glm::mat4 projection = glm::mat4(1.f),
                ShaderProgramRHPtr shader = nullptr);
    //TODO Texture
    void begin(const glm::mat4& view);
    //FIXME Naive drawing
    void drawOne(const glm::mat4& view, const Sprite& sprite);
    void drawOne(const glm::mat4& projection,
                 const glm::mat4& view, const Sprite& sprite);
    glm::mat4& projection() { return m_projection; }
    void end();

};
}
