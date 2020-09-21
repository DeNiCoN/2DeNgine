#include "Engine.hpp"
#include <resource/DirectoryFilesystem.hpp>
#include <tinyxml2.h>

INITIALIZE_EASYLOGGINGPP

namespace DeNgine
{


bool Engine::shouldClose()
{
    //TODO app should close
    return m_windowManager.shouldClose();
}

bool Engine::init(const tinyxml2::XMLElement& p_config)
{
    LOG(INFO) << "Engine initialization";
    //Initialize engine systems
    m_windowManager.initialize();
    m_renderManager.initialize();

    processConfigXML(p_config);
    LOG(INFO) << "Engine initialization finished";
    return true;
}

bool Engine::processConfigXML(const tinyxml2::XMLElement& p_config)
{
    auto* filesystems = p_config.FirstChildElement("Filesystems");
    if(!filesystems)
    {
        LOG(ERROR) << "Filesystems element in config not found";
    }
    else
    {
        for (auto* dir = filesystems->FirstChildElement("DirectoryFilesystem");
             dir; dir = dir->NextSiblingElement("DirectoryFilesystem"))
        {
            //FIXME Dynamic allocation
            const char* path = dir->Attribute("path");
            if (!path)
            {
                LOG(WARNING) << "No path attribute in DirectoryFilesystem node";
                continue;
            }
            m_resourceManager.addFilesystem(std::make_shared<DirectoryFilesystem>(path));
        }
    }

    const char* initialPath = p_config.Attribute("initialPath");
    if (!initialPath)
    {
        LOG(ERROR) << "No initial scene attribute in config file";
    }

    auto initialXml = m_xmlLoader.load(initialPath);
    if (!initialXml)
        return false;

    auto initial = m_sceneFactory.loadFromXML(initialXml->document().RootElement());
    if (!initial)
        return false;

    scenes.push_back(initial);
    return true;
}

bool Engine::run()
{
    LOG(INFO) << "Engine run";
    //loop
    while (!shouldClose())
    {
        m_currentTime = glfwGetTime();
        m_delta = m_currentTime - m_lastTime;
        m_lastTime = m_currentTime;
        m_delay += m_delta;
        while (m_delay >= SPF)
        {
            m_delay -= SPF;
            //TODO update
            for(auto scene : scenes)
            {
                scene->update(m_delta);
            }
        }
        //TODO render
        m_renderManager.render(m_delay / SPF);

        m_windowManager.poolEvents();
    }
    //TODO termination
    m_renderManager.terminate();
    m_windowManager.terminate();
    LOG(INFO) << "Engine finished successfully";
    return 0;
}
}
