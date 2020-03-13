#pragma once

#include <map>

#include "translationsDb/Translation.h"

using Dictionary = translationsDb::Translations;

using DictionaryName = std::string;

using Dictionaries = std::map<DictionaryName, Dictionary>;
