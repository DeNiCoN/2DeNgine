#include "gamebasis/ActorFactory.hpp"
#include <tinyxml2.h>
#include <iostream>

namespace DeNgine
{

Actor ActorFactory::loadFromXML(const Scene &scene,
                                const tinyxml2::XMLElement *root)
{
    Actor a = getNext();
    auto CMmap = scene.getComponentManagersMap();
    for (const tinyxml2::XMLElement* node = root->FirstChildElement();
         node; node = node->NextSiblingElement())
    {
        auto e = node->ToElement();
        if (!e)
            continue;
        auto c = CMmap.find(e->Value());
        if (c != CMmap.end())
        {
            if(!c->second.VLoadComponent(a, e))
            {
                std::cout << "Failed to load component " <<
                    c->second.VName().str << "\n";
                return 0;
            }
        }
        else
        {
            std::cout << "No component " << e->Value() << " in scene\n";
            return 0;
        }
    }
    return a;
}
}
