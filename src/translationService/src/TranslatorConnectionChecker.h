#pragma once

#include <string>

#include "TranslationApiConnectionStatus.h"

namespace glossary::translationService
{
class TranslatorConnectionChecker
{
public:
    virtual ~TranslatorConnectionChecker() = default;

    virtual TranslationApiConnectionStatus
    connectionToTranslatorWithApiKeyIsAvailable(const std::string& apiKey) = 0;
};
}