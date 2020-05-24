#pragma once

#include <string>

#include "TranslationApiStatus.h"

namespace glossary::translationService
{
class TranslatorConnectionChecker
{
public:
    virtual ~TranslatorConnectionChecker() = default;

    virtual TranslationApiStatus connectionToTranslatorWithApiKeyIsAvailable(const std::string& apiKey) = 0;
};
}