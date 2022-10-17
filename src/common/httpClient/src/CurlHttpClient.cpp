#include "CurlHttpClient.h"

#include "curl/curl.h"

#include "StringHelper.h"
#include "exceptions/ConnectionFailed.h"
#include "fmt/core.h"

namespace common::httpClient
{
namespace
{
size_t curlWriterCallback(char* data, size_t size, size_t nmemb, std::string* writerData)
{
    writerData->append(data, size * nmemb);

    return size * nmemb;
}
}

HttpResponse CurlHttpClient::get(const GetPayload& payload) const
{
    curl_global_init(CURL_GLOBAL_ALL);

    CURL* curl = curl_easy_init();

    if (not curl)
    {
        throw exceptions::ConnectionFailed("Error while initializing curl library");
    }

    HttpResponse response;

    std::vector<std::string> queryNamesWithValuesConcatenated;

    if (payload.queries)
    {
        for (const auto& query : *payload.queries)
        {
            queryNamesWithValuesConcatenated.push_back(fmt::format("{}={}", query.first, query.second));
        }
    }

    const auto joinedQueries = common::collection::join(queryNamesWithValuesConcatenated, "&");

    const auto url = payload.queries ? fmt::format("{}?{}", payload.url, joinedQueries) : payload.url;

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, payload.url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriterCallback);

    struct curl_slist* curlHeaders = nullptr;

    if (payload.headers)
    {
        for (const auto& header : *payload.headers)
        {
            curlHeaders = curl_slist_append(curlHeaders, header.c_str());
        }
    }

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);

    auto code = curl_easy_perform(curl);

    if ((code != CURLE_OK) || (response.data.empty()))
    {
        if (payload.headers)
        {
            curl_slist_free_all(curlHeaders);
        }

        curl_easy_cleanup(curl);
        curl_global_cleanup();

        throw exceptions::ConnectionFailed(
            fmt::format("Error while connecting to {}, code: {}", payload.url, curl_easy_strerror(code)));
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.statusCode);

    if (payload.headers)
    {
        curl_slist_free_all(curlHeaders);
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return response;
}
}