#pragma once

#include "resource/ResourceManager.hpp"
#include "tinyxml2.h"
#include <iostream>

namespace DeNgine
{

class XMLResourceLoader;

class XMLResourceData : public ResourceHandleData
{
    friend class XMLResourceLoader;
    tinyxml2::XMLDocument m_document;

    bool parseXml(char* pRawBuffer)
    {
        m_document.Parse(pRawBuffer);
        if (m_document.Error()) {
            std::cout << m_document.ErrorStr() << "\n";
            return false;
        }
        return true;
    }
};

class XMLResourceLoader
{
    XMLResourceLoader() = default;
    static XMLResourceLoader* instance;
public:
    static XMLResourceLoader* getInstance()
    {
        return instance ? instance : instance = new XMLResourceLoader();
    }

    ResourceHandlePtr load(ResourceManager& t_m, Resource& t_res,
                           IFileSystem* t_f = nullptr)
    {
        if (auto handle = t_m.getHandle(t_res))
        {
            return handle;
        }
        else
        {
            auto memory = t_m.loadToMemory(t_res, nullptr, t_f);
            auto data = new XMLResourceData();
            if (!data->parseXml(memory.get()))
            {
                delete data;
                return nullptr;
            }
            return t_m.newHandle(t_res, std::unique_ptr<ResourceHandleData>(data));
        }

    }
};
}
