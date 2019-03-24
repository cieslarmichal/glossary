#include "HTML_Reader.h"


std::string HTML_Reader::read_html(const std::string & url_address)
{
	std::string content;

	curl_global_init(CURL_GLOBAL_ALL);
	CURL * curl = nullptr;
	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url_address.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		CURLcode code = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	
	return content;
}

int HTML_Reader::writer(char * data, size_t size, size_t nmemb, std::string * writerData)
{
	if (writerData == NULL)
	{
		return 0;
	}

	writerData->append(data, size*nmemb);

	return size * nmemb;
}
