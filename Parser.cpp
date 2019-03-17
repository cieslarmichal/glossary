#include "Parser.h"

//comments >fetch</span> a doctor</span>  

std::string Parser::clean_line(const std::string & str)
{
	std::string result{ str };

	size_t open_sign_pos = result.find("<");
	size_t close_sign_pos = result.find(">");

	while ((open_sign_pos != std::string::npos) && (close_sign_pos != std::string::npos))
	{
		cut_off_string(result, open_sign_pos, close_sign_pos);
		open_sign_pos = result.find("<");
		close_sign_pos = result.find(">");
	}

	return result;
}

//not steady
void Parser::cut_off_string(std::string & line, size_t start_position, size_t end_position)
{
	std::string str1{ line }, str2{ line };

	str1 = str1.substr(0, start_position);
	str2 = str2.substr(end_position+1 , str2.size() - end_position);

	line = str1 + str2;
}

std::vector<std::string> Parser::parser_v0(const std::string && str)
{
	std::vector<std::string> parsed_sentences;
	std::stringstream sentences(str);
	std::string line;
	std::string pharse1{ "<span class=\"ex-sent t no-aq sents\">" };
	std::string pharse2{ "<span class=\"dtText\"><strong class=\"mw_t_bc\">: </strong>" };

	while (std::getline(sentences, line))
	{
		bool is_pharse1 = (line.find(pharse1) != std::string::npos);
		bool is_pharse2 = (line.find(pharse2) != std::string::npos);

		if (is_pharse1)
		{
			line += "eg";
		}
		if (is_pharse1 || is_pharse2)
		{
			//parsed_sentences.push_back(line);
			std::cout << clean_line(line) << std::endl << std::endl;
		}
	}

	return parsed_sentences;
}