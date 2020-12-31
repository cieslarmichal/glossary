#include "CurlHttpHandler.h"

#include "curl/curl.h"

#include "exceptions/ConnectionFailed.h"
#include "utils/GetProjectPath.h"

namespace webConnection
{

namespace
{
const std::string configPath{utils::getProjectPath("glossary") + "config"};
const std::string certificatePath{configPath + utils::slash + "cacert.pem"};
size_t curlWriterCallback(char* data, size_t size, size_t nmemb, std::string*);
}

Response CurlHttpHandler::get(const Request& urlAddress) const
{
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();

    if (not curl)
    {
        throw exceptions::ConnectionFailed("Error while initializing curl library");
    }

    Response response;
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_URL, urlAddress.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.content);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriterCallback);

    auto code = curl_easy_perform(curl);
    if ((code != CURLE_OK) || (response.content.empty()))
    {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        throw exceptions::ConnectionFailed("Error while connecting to: " + urlAddress + " " +
                                           curl_easy_strerror(code));
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.code);

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return response;
}

Response CurlHttpHandler::get(const std::string& url, const std::vector<std::string>& headers) const
{
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();

    if (not curl)
    {
        throw exceptions::ConnectionFailed("Error while initializing curl library");
    }

    Response response;
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.content);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriterCallback);

    struct curl_slist* curlHeaders = nullptr;
    for (const auto& header : headers)
    {
        curlHeaders = curl_slist_append(curlHeaders, header.c_str());
    }

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);

    auto code = curl_easy_perform(curl);
    if ((code != CURLE_OK) || (response.content.empty()))
    {
        curl_slist_free_all(curlHeaders);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        throw exceptions::ConnectionFailed("Error while connecting to: " + url + " " +
                                           curl_easy_strerror(code));
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.code);

    curl_slist_free_all(curlHeaders);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return response;
}

namespace
{
size_t curlWriterCallback(char* data, size_t size, size_t nmemb, std::string* writerData)
{
    writerData->append(data, size * nmemb);
    return size * nmemb;
}
}
}