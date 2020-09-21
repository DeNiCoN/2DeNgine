#pragma once
#include "utils/HashedString.hpp"
#include <functional>
#include "gamebasis/ComponentManager.hpp"
#include <string>
#include <unordered_map>

namespace DeNgine
{

class ComponentManagerFactory
{
    std::unordered_map<utils::HashedString,
                       std::function<IComponentManagerPtr()>> m_compFactories;
public:
    void registerComponent(utils::HashedString name,
                           std::function<IComponentManagerPtr()> factory)
    {
        m_compFactories[name] = factory;
    }

    IComponentManagerPtr create(utils::HashedString name) const
    {
        auto it = m_compFactories.find(name);
        if (it == m_compFactories.end())
        {
            return nullptr;
        }
        return it->second();
    }
};
}
