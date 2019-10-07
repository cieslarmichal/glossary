#pragma once

#include <map>
#include "Word.h"
#include "boost/optional.hpp"


template<class Key, class Object>
class Storage : private std::map<Key, Object>
{
public:
    explicit Storage(const std::map<Key, Object> &);

    void add(const Key &key, const Object &);
    boost::optional<Object> get(const Key &) const;
};
