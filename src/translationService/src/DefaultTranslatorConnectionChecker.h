#pragma once

#include <memory>

#include "TranslatorConnectionChecker.h"
#include "translator/Translator.h"

namespace glossary::translationService
{
class DefaultTranslatorConnectionChecker : public TranslatorConnectionChecker
{
public:
    explicit DefaultTranslatorConnectionChecker(std::shared_ptr<translator::Translator>);

    bool connectionToTranslatorWithApiKeyIsAvailable(const std::string& apiKey) override;

private:
    std::shared_ptr<translator::Translator> translator;
};
}