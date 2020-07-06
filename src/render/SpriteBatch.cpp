#include "render/SpriteBatch.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace DeNgine
{
unsigned SpriteBatch::s_vbo = 0;
bool SpriteBatch::s_initialized = false;

SpriteBatch::SpriteBatch(const RenderManager& rManager, glm::mat4 projection,
                         ShaderProgramRHPtr shader)
        : m_rManager(rManager), m_projection(projection), m_shader(shader)
{
    if(!s_initialized)
        init();
    if(!shader)
        m_shader = rManager.getShaderLoader().load
                ("Resources/basic.vert", "Resources/basic.frag");
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_transformBO);
    glGenBuffers(1, &m_colorBO);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, s_vbo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBO);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, m_transformBO);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)16);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)32);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)48);

    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteBatch::init()
{
    s_initialized = true;

    glGenBuffers(1, &s_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_quadData), m_quadData, GL_STATIC_DRAW);
}

/*void SpriteBatch::begin(const glm::mat4 &view)
{
    const ShaderProgramResourceData* shaderData =
        static_cast<const ShaderProgramResourceData*>(m_shader->data.get());
    glBindBuffer(GL_ARRAY_BUFFER, m_transformBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*16, NULL, GL_DYNAMIC_DRAW);
    auto transformBufferPtr = reinterpret_cast<float*>
        (glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

    glUseProgram(shaderData->shader);
    glm::mat4 projView = m_projection * view;
    glUniformMatrix4fv(
        glGetUniformLocation(shaderData->shader, "projectionView"),
        1, GL_FALSE, (GLfloat*)glm::value_ptr(projView));
}*/

void SpriteBatch::drawOne(const glm::mat4& p_world, const glm::mat4& p_view,
                          const glm::vec4& p_color)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_transformBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*16, glm::value_ptr(p_world), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4, glm::value_ptr(p_color), GL_DYNAMIC_DRAW);

    glUseProgram(m_shader->shader);
    glm::mat4 projView = m_projection * p_view;
    glUniformMatrix4fv(
        glGetUniformLocation(m_shader->shader, "projectionView"),
        1, GL_FALSE, (GLfloat*)glm::value_ptr(projView));

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
/*
void SpriteBatch::end()
{

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindVertexArray(s_vao);
}
*/
}
