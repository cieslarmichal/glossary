#include "factories/TranslationFactory.h"

#include "TranslationFactoryImpl.h"

namespace glossary::translation
{
std::unique_ptr<DictionaryFactory> DictionaryFactory::createTranslationFactory()
{
    return std::make_unique<DictionaryFactoryImpl>();
}
}
