#include "HTML_Parser.h"


const std::string HTML_Parser::prefix_url = "https://www.merriam-webster.com/dictionary/";


std::vector<std::string> HTML_Parser::filter_lines(const std::string & english_word)
{
	std::string html_content = english_word; //= HtmlFileReader::read_html(prefix_url + english_word);

	if (html_content.find("The word you've entered isn't in the dictionary") != std::string::npos)
	{
		return std::vector<std::string>{ "not found" };
	}

	std::vector<std::string> filtered_lines;
	std::stringstream sentences(html_content);

    //update examples code
    //<span class="ex-sent first-child t no-aq sents">blackberry <span class="mw_t_wi">wine</span></span>    itp
	std::string pharse1{ "<span class=\"ex-sent t no-aq sents\">" };
	std::string pharse2{ "<span class=\"ex-sent t has-aq sents\">" };
	std::string pharse3{ "<span class=\"dtText\"><strong class=\"mw_t_bc\">: </strong>" };
	std::string pharse4{ "<span class=\"t has-aq\">" };

	bool check_next_line = false;
	std::string line;

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
		    std::cerr<<"XxxxxxX"<<std::endl;
			line += "~eg";
		}
		if (is_pharse1 || is_pharse2 || is_pharse3)
		{
			filtered_lines.push_back(remove_html_tags(line));
			continue;
		}

		if (check_next_line)
		{
			line += "~sentence";
			filtered_lines.push_back(remove_html_tags(line));
			check_next_line = false;
			continue;
		}

		if (is_pharse4)
		{
			line += "~sentence";
			filtered_lines.push_back(remove_html_tags(line));
		}
	}

	return filtered_lines;
}

std::string HTML_Parser::remove_html_tags(const std::string & str)
{
	std::string result{ str };

	size_t open_sign_pos = result.find("<");
	size_t close_sign_pos = result.find(">");

	while ((open_sign_pos != std::string::npos) && (close_sign_pos != std::string::npos))
	{
		result = String_Additives::cut_off_string(result, open_sign_pos, close_sign_pos);
		open_sign_pos = result.find("<");
		close_sign_pos = result.find(">");
	}

	open_sign_pos = result.find("&mdash;");
	while (open_sign_pos != std::string::npos)
	{
		result = String_Additives::cut_off_string(result, open_sign_pos, open_sign_pos + 6);
		open_sign_pos = result.find("&mdash;");
	}

	open_sign_pos = result.find("&quot;");
	while (open_sign_pos != std::string::npos)
	{
		result.at(open_sign_pos) = '\"';
		result = String_Additives::cut_off_string(result, open_sign_pos + 1, open_sign_pos + 5);
		open_sign_pos = result.find("&quot;");
	}

	String_Additives::trim(result);

	return result;
}


