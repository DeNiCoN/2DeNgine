#include "gamebasis/ActorFactory.hpp"
#include <easylogging++.h>
#include <tinyxml2.h>
#include <iostream>

namespace DeNgine
{


Actor ActorFactory::loadFromXML(Scene &scene,
                                const tinyxml2::XMLElement *root)
{
    if (!root)
    {
        LOG(ERROR) << "Null element passed to actor factory";
        return 0;
    }
    Actor a = getNext();
    auto& CMmap = scene.getComponentManagersMap();
    for (const tinyxml2::XMLElement* node = root->FirstChildElement();
         node; node = node->NextSiblingElement())
    {
        if (!node)
            continue;

        auto& CMMap = scene.getComponentManagersMap();
        auto comp = CMMap.find(node->Value());
        if (comp != CMMap.end())
        {
            if(!comp->second->VLoadComponent(a, node))
            {
                LOG(ERROR) << "Failed to load component " <<
                    node->Value();
                return 0;
            }
        }
        else
        {
            LOG(ERROR) << node->Value() << " not found while loading scene";
            return 0;
        }
    }
    return a;
}
}
