#pragma once

#include <string>

namespace glossary::translationService
{
class TranslatorConnectionChecker
{
public:
    virtual ~TranslatorConnectionChecker() = default;

    virtual bool connectionToTranslatorWithApiKeyIsAvailable(const std::string& apiKey) = 0;
};
}