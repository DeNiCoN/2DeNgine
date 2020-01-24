#ifndef __LRUCACHE_H_
#define __LRUCACHE_H_
#include <list>
#include <cassert>
#include <unordered_map>

template<typename K, typename V>
class LRUCache
{
    using List = std::list<std::pair<K, V>>;
    std::unordered_map<K, typename List::iterator> m_hashmap;
    List m_LRUList;

public:

    typename List::const_iterator find(const K& key)
    {
        auto value = m_hashmap.find(key);
        if (value != m_hashmap.end())
        {
            m_LRUList.splice(m_LRUList.begin(), m_LRUList, value->second);
            return value->second;
        }
        else
        {
            return m_LRUList.end();
        }
    }

    void insert(const K& key, const V& value)
    {
        assert(m_hashmap.find(key) == m_hashmap.end()
        && "key already in cache, you can't change it value");
        m_LRUList.push_front(std::make_pair(key, value));
        m_hashmap[key] = m_LRUList.begin();
    }

    void removeOne()
    {
        assert(size() && "removeOne() on empty cache");
        m_hashmap.erase(m_LRUList.back().first);
        m_LRUList.pop_back();
    }

    typename List::const_iterator end()
    {
        return m_LRUList.end();
    }

    typename List::const_iterator begin()
    {
        return m_LRUList.begin();
    }

    bool empty()
    {
        return begin() == end();
    }

    std::size_t size()
    {
        return m_hashmap.size();
    }

    std::pair<K, V>& back()
    {
        assert(size() && "back() on empty cache");
        return m_LRUList.back();
    }
};

#endif // __LRUCACHE_H_
