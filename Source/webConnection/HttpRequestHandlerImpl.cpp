#include "webConnection/HttpRequestHandlerImpl.h"

#include "curl/curl.h"
#include "exceptions/ConnectionFailed.h"

namespace webConnection
{

namespace
{
size_t curlWriter(char* data, size_t size, size_t nmemb, std::string*);
}

Response HttpRequestHandlerImpl::get(const Request& urlAddress) const
{
    Response response;

    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, urlAddress.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.content);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriter);

        if ((curl_easy_perform(curl) != CURLE_OK) || (response.content.empty()))
        {
            curl_easy_cleanup(curl);
            throw exceptions::ConnectionFailed("Error while connecting to: " +
                                               urlAddress);
        }

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.code);

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return response;
}

namespace
{
size_t curlWriter(char* data, size_t size, size_t nmemb,
                  std::string* writerData)
{
    writerData->append(data, size * nmemb);
    return size * nmemb;
}
}
}