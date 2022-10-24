#include "GetSupportedLanguagesQueryImpl.h"

namespace glossary::translation
{
std::vector<Language> GetSupportedLanguagesQueryImpl::getSupportedLanguages() const
{
    return {Language::Polish, Language::English};
}

}
