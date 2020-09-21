#pragma once

#include "resource/ResourceManager.hpp"
#include "tinyxml2.h"
#include <easylogging++.h>
#include <iostream>

namespace DeNgine
{

class XMLResourceLoader;

class XMLResourceHandle
{
    friend class XMLResourceLoader;
    tinyxml2::XMLDocument m_document;

public:
    const tinyxml2::XMLDocument& document() const { return m_document; }

    XMLResourceHandle(char* p_source)
    {
        m_document.Parse(p_source);
    }
};

using XMLResourceHandlePtr = std::shared_ptr<XMLResourceHandle>;

class XMLResourceLoader
{
    mutable LRUCache<Resource, XMLResourceHandlePtr> m_documentCache;
    const ResourceManager& m_resManager;
public:

    XMLResourceLoader(const ResourceManager& p_resManager)
        : m_resManager(p_resManager) {}

    XMLResourceHandlePtr load(const Resource& p_res)
    {
        if (m_documentCache.count(p_res))
        {
            return m_documentCache.at(p_res);
        }
        else
        {
            auto memory = m_resManager.loadToMemory(p_res, true);
            if (!memory)
                return nullptr;
            auto handle = std::make_shared<XMLResourceHandle>(memory.get());
            if (handle->document().Error()) {
                LOG(ERROR) << "Failed to load XML file: "
                           << handle->document().ErrorStr();
                return nullptr;
            }
            return handle;
        }

    }
};
}
