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
	std::string cleared_line{ line };
	size_t space_position = -1;
	size_t index = 0;
	size_t size_to_cut = 0;

	for (index = 0; index < cleared_line.size(); ++index)
	{
		if (isspace(cleared_line.at(index)))
		{
			if (size_to_cut == 0)
			{
				space_position = index;
			}
			size_to_cut++;
		}
		else if ((size_to_cut > 1) && (space_position != -1))
		{
			if (space_position == 0)
			{
				cleared_line = cut_off_string(cleared_line, space_position, space_position + size_to_cut - 1);
			}
			else
			{
				cleared_line = cut_off_string(cleared_line, space_position + 1, space_position + size_to_cut - 1);
			}
			index = -1;
			size_to_cut = 0;
			space_position = -1;
		}
		else
		{
			space_position = -1;
			size_to_cut = 0;
		}
	}

	return cleared_line;
}

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
	std::string pharse2{ "<span class=\"ex-sent t has-aq sents\">" };
	std::string pharse3{ "<span class=\"dtText\"><strong class=\"mw_t_bc\">: </strong>" };
	std::string pharse4{ "<span class=\"t has-aq\">" };

	bool check_next_line = false;

	while (std::getline(sentences, line))
	{
		bool is_pharse1 = (line.find(pharse1) != std::string::npos);
		bool is_pharse2 = (line.find(pharse2) != std::string::npos);
		bool is_pharse3 = (line.find(pharse3) != std::string::npos);
		bool is_pharse4 = (line.find(pharse4) != std::string::npos);


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
			continue;
		}

		if (check_next_line)
		{
			line += "~sentence";
			parsed_sentences.push_back(clean_line(line));
			check_next_line = false;
			continue;
		}

		if (is_pharse4)
		{
			line += "~sentence";
			parsed_sentences.push_back(clean_line(line));
		}

	}

	return parsed_sentences;
}