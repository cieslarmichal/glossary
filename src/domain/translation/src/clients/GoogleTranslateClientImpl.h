#pragma once

#include <memory>

#include "GoogleTranslateApiResponse.h"
#include "GoogleTranslateClient.h"
#include "GoogleTranslateClientConfig.h"
#include "httpClient/HttpClient.h"
#include "TranslatePayload.h"

namespace glossary::translation
{
class GoogleTranslateClientImpl : public GoogleTranslateClient
{
public:
    GoogleTranslateClientImpl(std::shared_ptr<const common::httpClient::HttpClient>,
                              GoogleTranslateClientConfig);

    std::string translate(const TranslatePayload&) const override;

private:
    common::httpClient::HttpGetRequestPayload prepareRequestPayload(const TranslatePayload&) const;
    GoogleTranslateApiResponse parseGoogleTranslateResponseBody(const std::string& responseBody) const;

    std::shared_ptr<const common::httpClient::HttpClient> httpClient;
    const GoogleTranslateClientConfig config;
};
}
