#pragma once
#include "resource/ResourceManager.hpp"
#include "glad/glad.h"
//#include "render/RenderManager.hpp"

namespace DeNgine
{
class ShaderResourceLoader;



class ShaderRH
{
public:
    ShaderRH(const Resource& p_res, char* p_source, unsigned p_type)
        : shader(glCreateProgram()), type(p_type), resource(p_res)
    {
        glShaderSource(shader, 1, &p_source, NULL);
        glCompileShader(shader);
    }
    const unsigned int shader;
    const unsigned int type;
    const Resource resource;

    ~ShaderRH()
    {
        if (shader)
        {
            glDeleteShader(shader);
        }
    }
};

class ShaderProgramRH
{
public:
    ShaderProgramRH(const Resource& p_res, ShaderRH& vertex, ShaderRH& fragment)
        : resource(p_res), shader(glCreateProgram())
    {
        glAttachShader(shader, vertex.shader);
        glAttachShader(shader, fragment.shader);
        glLinkProgram(shader);
    }
    const Resource resource;
    const unsigned int shader;
    ~ShaderProgramRH()
    {
        if (shader)
        {
            glDeleteProgram(shader);
        }
    }
};

using ShaderProgramRHPtr = std::shared_ptr<ShaderProgramRH>;
using ShaderRHPtr = std::shared_ptr<ShaderRH>;

//Inheritance just for future ability to preload resources
class ShaderResourceLoader final : public IResourceLoader
{
    mutable LRUCache<Resource, ShaderProgramRHPtr> m_programCache;
    mutable LRUCache<Resource, ShaderRHPtr> m_shaderCache;
    ResourceManager& m_manager;

public:
    ShaderResourceLoader(ResourceManager& p_manager)
        : m_manager(p_manager)
    {}

    //Basic shader loader. Loads shaders from vertex and fragment files
    ShaderProgramRHPtr load(const Resource& vertex, const Resource& fragment) const;
    ShaderRHPtr loadShader(const Resource& vertex, int p_type) const;
    //TODO wait
    //std::initializer_list<const char*> VGetExtensions override
    //{
    //    return {"vert", "frag", "geom", "tessc", }
    //}
};

}
