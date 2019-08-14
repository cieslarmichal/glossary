#include "HtmlReaderImpl.h"

#include "curl/curl.h"

namespace
{
int curlWriter(char *data, size_t size, size_t nmemb, std::string *);
const std::string connectionErrorMessage{"Error while connecting to: "};
}

std::string HtmlReaderImpl::read(const std::string & urlAddress) const
{
    std::string content;

    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, urlAddress.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriter);

        while ((curl_easy_perform(curl) != CURLE_OK) || (content.size() == 0))
        {
            curl_easy_cleanup(curl);
            throw ConnectionFailed(connectionErrorMessage + urlAddress);
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return content;
}

namespace
{

int curlWriter(char *data, size_t size, size_t nmemb, std::string *writerData)
{
    if (writerData == nullptr)
    {
        return 0;
    }

    writerData->append(data, size * nmemb);

    return size * nmemb;
}

}



