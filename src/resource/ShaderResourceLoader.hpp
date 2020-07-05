#pragma once
#include "resource/ResourceManager.hpp"
#include "glad/glad.h"
//#include "render/RenderManager.hpp"

namespace DeNgine
{

class ShaderProgramResourceData final : public ResourceHandleData
{
public:
    unsigned int shader;
    ShaderProgramResourceData(unsigned p_shader)
        : shader(p_shader)
    {}
    ~ShaderProgramResourceData() override
    {
        if (shader)
        {
            glDeleteProgram(shader);
        }
    }
};

class ShaderResourceData : public ResourceHandleData
{
public:
    ShaderResourceData(unsigned p_shader, unsigned p_type)
        : shader(p_shader), type(p_type)
    {}
    unsigned int shader;
    unsigned int type;
    ~ShaderResourceData()
    {
        if (shader)
        {
            glDeleteShader(shader);
        }
    }
};

class ShaderResourceLoader final : public IResourceLoader
{
    ResourceManager& m_manager;
public:
    ShaderResourceLoader(ResourceManager& p_manager)
        : m_manager(p_manager)
    {}

    //Basic shader loader. Loads shaders from vertex and fragment files
    ResourceHandlePtr load(const Resource& vertex, const Resource& fragment) const;
    ResourceHandlePtr loadShader(const Resource& vertex, int p_type) const;
    //TODO wait
    //std::initializer_list<const char*> VGetExtensions override
    //{
    //    return {"vert", "frag", "geom", "tessc", }
    //}
};

}
