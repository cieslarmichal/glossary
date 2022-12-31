#include "factories/TranslationFactory.h"

#include "TranslationFactoryImpl.h"

namespace glossary::translation
{
std::unique_ptr<TranslationFactory> TranslationFactory::createTranslationFactory()
{
    return std::make_unique<TranslationFactoryImpl>();
}
}
