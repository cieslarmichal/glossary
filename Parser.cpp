#include "Parser.h"


std::string Parser::clean_line(const std::string & str)
{
	std::string result{ str };

	size_t open_sign_pos = result.find("<");
	size_t close_sign_pos = result.find(">");

	while ((open_sign_pos != std::string::npos) && (close_sign_pos != std::string::npos))
	{
		result = cut_off_string(result, open_sign_pos, close_sign_pos);
		open_sign_pos = result.find("<");
		close_sign_pos = result.find(">");
	}

	open_sign_pos = result.find("&mdash;");
	if (open_sign_pos != std::string::npos)
	{
		result = cut_off_string(result, open_sign_pos, open_sign_pos + 7);

	}

	result = remove_spaces(result);

	return result;
}

std::string Parser::remove_spaces(const std::string & line)
{
	size_t index = 0;

	for (; (index<line.size() && isspace(line.at(index))); ++index);

	if (index>0 )
	{
		return cut_off_string(line, 0, index - 1);

	}
	else
	{
		return line;
	}
}

//not steady
std::string Parser::cut_off_string(const std::string & line, size_t start_position, size_t end_position)
{
	std::string str1{ line }, str2{ line };

	str1 = str1.substr(0, start_position);
	str2 = str2.substr(end_position + 1, str2.size() - end_position);

	return (str1 + str2);
}

std::vector<std::string> Parser::parser_v0(const std::string & str)
{
	std::fstream file;
	file.open("code_to_parse.txt", std::ios::out);

	if (!file.good())
	{
		std::cout << "chujowy plik txt \n";
	}
	file << str;
	file.close();

	std::vector<std::string> parsed_sentences;
	std::stringstream sentences(str);
	std::string line;
	std::string pharse1{ "<span class=\"ex-sent t no-aq sents\">" };
	//<span class=\"mw_t_wi\">
	std::string pharse2{ "<span class=\"ex-sent t has-aq sents\">" };
	std::string pharse3{ "<span class=\"dtText\"><strong class=\"mw_t_bc\">: </strong>" };

	bool check_next_line = false;

	while (std::getline(sentences, line))
	{
		bool is_pharse1 = (line.find(pharse1) != std::string::npos);
		bool is_pharse2 = (line.find(pharse2) != std::string::npos);
		bool is_pharse3 = (line.find(pharse3) != std::string::npos);

		if (is_pharse1)
		{
			check_next_line = true;
		}

		if ((is_pharse1 || is_pharse2) && line != pharse1 && line != pharse2)
		{
			line += "~eg";
		}
		if (is_pharse1 || is_pharse2 || is_pharse3)
		{
			parsed_sentences.push_back(clean_line(line));
			//std::cout << clean_line(line) << std::endl << std::endl;
			continue;
		}

		if (check_next_line)
		{
			line += "~sentence";
			parsed_sentences.push_back(clean_line(line));
			//std::cout << clean_line(line) << std::endl << std::endl;
			check_next_line = false;
			continue;
		}
	}



	return parsed_sentences;
}