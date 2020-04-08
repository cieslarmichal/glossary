#pragma once

#include <vector>

#include "translator/Language.h"

namespace glossary::translationService
{
class SupportedLanguagesRetriever
{
public:
    std::vector<std::string> retrieveSupportedLanguages() const;

private:
    static const std::vector<translator::Language> supportedLanguages;
};
}
