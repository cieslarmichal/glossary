#pragma once

#include "WordRandomizer.h"
#include "utils/RandomNumberGenerator.h"
#include <memory>

namespace glossary
{
class DefaultWordRandomizer : public WordRandomizer
{
public:
    explicit DefaultWordRandomizer(std::shared_ptr<utils::RandomNumberGenerator>);

    Word randomizeWord(const Words&) const override;

private:
    std::shared_ptr<utils::RandomNumberGenerator> randomNumberGenerator;
    Words::size_type getRandomIndex(Words::size_type) const;
};
}