#pragma once

#include "wordDescriptionRepository/WordDescription.h"

namespace glossary::wordDescriptionDownloader
{
class WordDescriptionResponseDeserializer
{
public:
    virtual ~WordDescriptionResponseDeserializer() = default;

    virtual wordDescriptionRepository::Definitions deserializeDefinitions(const std::string&) const = 0;
    virtual wordDescriptionRepository::Examples deserializeExamples(const std::string&) const = 0;
    virtual wordDescriptionRepository::Synonyms deserializeSynonyms(const std::string&) const = 0;
};
}