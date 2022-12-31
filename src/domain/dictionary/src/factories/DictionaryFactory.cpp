#include "factories/DictionaryFactory.h"

#include "DictionaryFactoryImpl.h"

namespace glossary::dictionary
{
std::unique_ptr<DictionaryFactory> DictionaryFactory::createDictionaryFactory()
{
    return std::make_unique<DictionaryFactoryImpl>();
}
}
