#pragma once

#include <vector>

namespace glossary::dictionary
{
class WordDescriptionResponseDeserializer
{
public:
    virtual ~WordDescriptionResponseDeserializer() = default;

    virtual std::vector<std::string> deserializeDefinitions(const std::string&) const = 0;
    virtual std::vector<std::string> deserializeExamples(const std::string&) const = 0;
    virtual std::vector<std::string> deserializeSynonyms(const std::string&) const = 0;
};
}