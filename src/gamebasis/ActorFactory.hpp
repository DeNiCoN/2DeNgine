#ifndef __ACTORFACTORY_H_
#define __ACTORFACTORY_H_
#include "gamebasis/Scene.hpp"

namespace DeNgine
{
class ActorFactory
{
    ActorFactory() = default;
    static ActorFactory* instance;

    Actor m_next;
    Actor getNext()
    {
        return m_next++;
    }

public:

    Actor loadFromXML(const Scene& scene, const tinyxml2::XMLElement* root);
    static ActorFactory* getInstance()
    {
        return instance ? instance : instance = new ActorFactory();
    }
};

}
#endif
