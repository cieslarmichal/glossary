#include "wordsDb/translationsDb/TranslationsSerializerImpl.h"

namespace wordsDb::translationsDb
{

std::string TranslationsSerializerImpl::serialize(const Translations&) const
{
    return std::__cxx11::string();
}

Translations TranslationsSerializerImpl::deserialize(const std::string&) const
{
    return wordsDb::translationsDb::Translations();
}

}