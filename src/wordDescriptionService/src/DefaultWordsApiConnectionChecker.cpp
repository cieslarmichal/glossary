#include "DefaultWordsApiConnectionChecker.h"
#include "webConnection/exceptions/ConnectionFailed.h"
#include "wordDescriptionDownloader/exceptions/InvalidApiKey.h"

namespace glossary::wordDescriptionService
{
namespace
{
const std::string exampleEnglishWord{"fish"};
}

DefaultWordsApiConnectionChecker::DefaultWordsApiConnectionChecker(
    std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader> downloader)
    : wordDescriptionDownloader{std::move(downloader)}
{
}

WordsApiStatus DefaultWordsApiConnectionChecker::connectionToWordsApiAvailable()
{
    try
    {
        wordDescriptionDownloader->tryDownloadWordDescription(exampleEnglishWord);
        return WordsApiStatus::Available;
    }
    catch (const webConnection::exceptions::ConnectionFailed& e)
    {
        std::cerr << "Connection to words api is not availavile"<< e.what();
        return WordsApiStatus::Unavailable;
    }
    catch (const wordDescriptionDownloader::exceptions::InvalidApiKey& e)
    {
        std::cerr << "Invalid api key: " << e.what();
        return WordsApiStatus::InvalidApiKey;
    }
}

}