#pragma once

#include <map>

#include "translationRepository/Translation.h"

using Dictionary = translationRepository::Translations;

using DictionaryName = std::string;

using Dictionaries = std::map<DictionaryName, Dictionary>;
