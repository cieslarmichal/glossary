#pragma once

#include <memory>

#include "WordsApiConnectionChecker.h"
#include "wordDescriptionDownloader/WordDescriptionDownloader.h"

namespace glossary::wordDescriptionService
{
class DefaultWordsApiConnectionChecker : public WordsApiConnectionChecker
{
public:
    explicit DefaultWordsApiConnectionChecker(
        std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>);

    WordsApiStatus connectionToWordsApiAvailable(const std::string& wordsApiKey) const override;

private:
    std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader> wordDescriptionDownloader;
};
}