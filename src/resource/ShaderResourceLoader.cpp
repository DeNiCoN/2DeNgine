#include "resource/ShaderResourceLoader.hpp"
#include <easylogging++.h>
#include <iostream>

namespace DeNgine
{

ShaderProgramRHPtr ShaderResourceLoader::load(const Resource& p_vertex,
                                              const Resource& p_fragment) const
{
    //Concatenate shader names to unique identify shader
    //TODO performance
    std::string concatStr;
    concatStr += p_vertex.str;
    concatStr += p_fragment.str;
    Resource concat(concatStr.c_str());
    //Check for cached resource
    if (m_programCache.count(concat))
    {
        return m_programCache.at(concat);
    }
    else
    {
        //Load shaders
        //Check if any errors occured
        auto vertex = loadShader(p_vertex, GL_VERTEX_SHADER);
        if (!vertex)
        {
            LOG(ERROR) << "Failed to load vertex shader resource " <<
                p_vertex.str << " while loading shader program";
            return nullptr;
        }
        auto fragment = loadShader(p_fragment, GL_FRAGMENT_SHADER);
        if (!fragment)
        {
            LOG(ERROR) << "Failed to load vertex shader resource " <<
                p_vertex.str << " while loading shader program";
            return nullptr;
        }

        //Create and link shader
        //FIXME Dynamic allocation
        auto handle = std::make_shared<ShaderProgramRH>
            (concat, *vertex.get(), *fragment.get());

        int success;
        glGetProgramiv(handle->shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            static char message[512];
            glGetProgramInfoLog(vertex->shader, 512, NULL, message);
            LOG(ERROR) << "Failed to link shader program: " << message;
            return nullptr;
        }
        //Insert it into cache
        m_programCache.insert(concat, handle);
        return handle;
    }
}

ShaderRHPtr ShaderResourceLoader::loadShader(const Resource& p_shader,
                                                   int p_type) const
{
    //Check for cached resource
    if (m_shaderCache.count(p_shader))
    {
        return m_shaderCache.at(p_shader);
    }
    else
    {
        //Load \0 separated string from p_shader file
        auto mem = m_manager.loadToMemory(p_shader, true);

        if (!mem)
            return nullptr;

        char* mem2 = mem.get();

        //Compile shader
        //FIXME Dynamic allocation
        auto handle = std::make_shared<ShaderRH>
            (p_shader, mem2, p_type);

        //Check for errors
        int success;
        glGetShaderiv(handle->shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            static char message[512];
            glGetShaderInfoLog(handle->shader, 512, NULL, message);
            LOG(ERROR) << "Failed to compile shader: " << message;
            return nullptr;
        };

        m_shaderCache.insert(p_shader, handle);
        return handle;
    }
}

}
