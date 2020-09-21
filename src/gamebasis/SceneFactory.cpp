#include "gamebasis/SceneFactory.hpp"
#include <string>
#include "gamebasis/ActorFactory.hpp"

namespace DeNgine
{

IComponentManagerPtr checkAndAdd(Scene& p_scene,
                 const ComponentManagerFactory& p_CMFactory,
                 utils::HashedString p_component)
{
    auto& CMmap = p_scene.getComponentManagersMap();
    auto c = CMmap.find(p_component);
    if (c != CMmap.end())
    {
        return c->second;
    }
    else
    {
        auto comp = p_CMFactory.create(p_component);
        if (!comp)
        {
            return nullptr;
        }
        p_scene.addComponentManager(comp);
        return comp;
    }
}

ScenePtr SceneFactory::loadFromXML(const tinyxml2::XMLElement *p_root)
{
    if (!p_root)
    {
        LOG(ERROR) << "Null element passed to scene factory";
        return nullptr;
    }

    ScenePtr scene = std::make_shared<Scene>();

    auto* viewport = p_root->FirstChildElement("Viewport");
    if (!viewport)
    {
        LOG(WARNING) << "No viewport specified while loading scene. Using screen"
            "viewport as default";
        scene->m_viewportType = ViewportType::SCREEN;
    }
    else
    {
        const char* viewportStr = viewport->Value();
        if (strcmp(viewportStr, "Screen") == 0)
        {
            scene->m_viewportType = ViewportType::SCREEN;
        }
        else
        {
            LOG(WARNING) << "No such viewport with name" << viewportStr <<
                "using screen viewport as default";
        }
    }

    auto* components = p_root->FirstChildElement("Components");

    if (!components)
    {
        LOG(WARNING) << "No components node";
    }
    else
    {
        for (auto* it = components->FirstChildElement();
             it; it = it->NextSiblingElement())
        {
            checkAndAdd(*scene.get(), m_CMFactory, it->Value());
        }

        for (auto& [str, component] : scene->m_CMmap)
        {
            component->VInit(*scene.get());
        }
    }

    auto* actors = p_root->FirstChildElement("Actors");
    if (actors)
    {
        for (auto* it = actors->FirstChildElement("Actor");
             it; it = it->NextSiblingElement("Actor"))
        {
            m_actorFactory.loadFromXML(*scene.get(), it);
        }
    }
    return scene;
}

}
