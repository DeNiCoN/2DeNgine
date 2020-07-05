#include "resource/ShaderResourceLoader.hpp"
#include <easylogging++.h>
#include <iostream>

namespace DeNgine
{

ResourceHandlePtr ShaderResourceLoader::load(const Resource& p_vertex,
                                             const Resource& p_fragment) const
{
    //Concatenate shader names to unique identify shader
    //TODO performance
    std::string concatStr;
    concatStr += p_vertex.str;
    concatStr += p_fragment.str;
    Resource concat(concatStr.c_str());
    //Check for cached resource
    auto handle = m_manager.getHandle(concat);
    if (!handle)
    {
        //Load shaders
        //Check if any errors occured
        ResourceHandlePtr vertex = loadShader(p_vertex, GL_VERTEX_SHADER);
        if (!vertex)
        {
            LOG(ERROR) << "Failed to load vertex shader resource " <<
                p_vertex.str << " while loading shader program";
            return handle;
        }
        ResourceHandlePtr fragment = loadShader(p_fragment, GL_FRAGMENT_SHADER);
        if (!fragment)
        {
            LOG(ERROR) << "Failed to load vertex shader resource " <<
                p_vertex.str << " while loading shader program";
            return handle;
        }
        //Get resource data's
        auto vertexData = reinterpret_cast<const ShaderResourceData*>
            (vertex.get()->data.get());
        auto fragmentData = reinterpret_cast<const ShaderResourceData*>
            (fragment.get()->data.get());

        //TODO load from renderManager. Doing direct opengl call for now
        //Create and link shader
        int program = glCreateProgram();
        glAttachShader(program, vertexData->shader);
        glAttachShader(program, fragmentData->shader);
        glLinkProgram(program);
        int success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            static char message[512];
            glGetProgramInfoLog(vertexData->shader, 512, NULL, message);
            LOG(ERROR) << "Failed to link shader program: " << message;
            return handle;
        }
        //Create ShaderProgramResourceData
        //FIXME Dynamic allocation
        auto data = std::make_unique<ShaderProgramResourceData>(program);
        handle = m_manager.newHandle(concat, std::move(data));
    }
    return handle;
}

ResourceHandlePtr ShaderResourceLoader::loadShader(const Resource& p_shader,
                                                   int p_type) const
{
    //Check for cached resource
    auto handle = m_manager.getHandle(p_shader);
    if (!handle)
    {
        //Load \0 separated string from p_shader file
        auto mem = m_manager.loadToMemory(p_shader, true);

        if (!mem)
            return handle;

        //Compile shader
        //TODO load from renderManager. Doing direct opengl call for now
        char* mem2 = mem.get();
        unsigned shader = glCreateShader(p_type);
        glShaderSource(shader, 1, &mem2, NULL);
        glCompileShader(shader);
        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            static char message[512];
            glGetShaderInfoLog(shader, 512, NULL, message);
            LOG(ERROR) << "Failed to compile shader: " << message;
            return handle;
        };
        //Create ShaderResourceData
        auto data = std::make_unique<ShaderResourceData>(shader, p_type);
        handle = m_manager.newHandle(p_shader, std::move(data));
    }
    return handle;
}

}
