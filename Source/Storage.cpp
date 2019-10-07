#include "Storage.h"
#include <tuple>

template<class Key, class Object>
Storage<Key, Object>::Storage(const std::map<Key, Object> &objects) : std::map<Key, Object>(objects)
{
}

template<class Key, class Object>
void Storage<Key, Object>::add(const Key &key, const Object &word)
{
    std::map<Key, Object>::insert({key, word});
}

template<class Key, class Object>
boost::optional<Object> Storage<Key, Object>::get(const Key &key) const
{
    if (std::map<Key, Object>::find(key) != std::map<Key, Object>::end())
    {
        return std::map<Key, Object>::at(key);
    }

    return boost::none;
}
