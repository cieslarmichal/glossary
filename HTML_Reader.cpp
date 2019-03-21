#include "HTML_Reader.h"

const std::string HTML_Reader::prefix_url = "https://www.merriam-webster.com/dictionary/";

std::vector<std::string> HTML_Reader::read_html(const std::string & english_word)
{
	std::string content;

	curl_global_init(CURL_GLOBAL_ALL);
	CURL * curl = nullptr;
	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, (prefix_url + english_word).c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		CURLcode code = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	std::cout << "HTMLRDR";
	return Parser::parser_v0(content);
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
