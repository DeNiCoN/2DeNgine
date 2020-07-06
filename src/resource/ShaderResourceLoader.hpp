#pragma once
#include "resource/ResourceManager.hpp"
#include "glad/glad.h"
//#include "render/RenderManager.hpp"

namespace DeNgine
{
class ShaderResourceLoader;


class ShaderProgramRH
{
    friend class ShaderResourceLoader;
    struct _private_ { explicit _private_() = default; };
public:
    ShaderProgramRH(_private_, const Resource& p_res,
                                unsigned p_shader)
        : shader(p_shader), resource(p_res) {}
    unsigned int shader;
    const Resource resource;
    ~ShaderProgramRH()
    {
        if (shader)
        {
            glDeleteProgram(shader);
        }
    }
};
using ShaderProgramRHPtr = std::shared_ptr<ShaderProgramRH>;

class ShaderRH
{
    friend class ShaderResourceLoader;
    struct _private_ { explicit _private_() = default; };
public:
    ShaderRH(_private_, const Resource& p_res,
                                unsigned p_shader, unsigned p_type)
        : shader(p_shader), type(p_type), resource(p_res) {}
    const Resource resource;
    const unsigned int shader;
    const unsigned int type;
    ~ShaderRH()
    {
        if (shader)
        {
            glDeleteShader(shader);
        }
    }
};
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
