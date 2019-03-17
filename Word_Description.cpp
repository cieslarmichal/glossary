#include "Word_Description.h"

const std::vector<std::string> Word_Description::key_words{ "~eg" ,"~sentence"};


Word_Description::Word_Description(std::vector<std::string> inp)
{
	clean_input(inp);
	split_input(inp);
}

void Word_Description::clean_input(std::vector<std::string> & inp)
{
	inp.erase(std::remove_if(inp.begin(), inp.end(), [](std::string line)
	{return ((line == "") || (line == key_words.at(0)) || line == key_words.at(1)); }), inp.end());
}

void Word_Description::split_input(const std::vector<std::string> & inp)
{
	bool example_flag = false;

	std::string definition, example,sentence;

	for (auto line : inp)
	{
		size_t pharse1_position = line.find(key_words.at(0));
		size_t pharse2_position = line.find(key_words.at(1));

		bool is_pharse1 = (pharse1_position != std::string::npos);
		bool is_pharse2 = (pharse2_position != std::string::npos);

		if (example_flag && !is_pharse1)
		{
			add_defition_example(definition, "");
			example_flag = false;
		}

		if (is_pharse2)
		{
			sentence = line;
			sentence = line.substr(0, pharse2_position);
			add_sentence(sentence);
			continue;
		}

		if (example_flag && is_pharse1)
		{
			example = line;
			example = example.substr(0, pharse1_position);
			add_defition_example(definition, example);
			example_flag = false;
		}

		if (line.at(0) == ':')
		{
			definition = line;
			example_flag = true;
		}

	}

	for (auto def_eg : definitions_examples)
	{
		std::cout << "def " << def_eg.first << std::endl;
		std::cout << "e.g. " << def_eg.second << std::endl;
		std::cout << std::endl;
	}

	for (auto s : sentences)
	{
		std::cout << "sentence: " << s << std::endl;
		std::cout << std::endl;
	}
}

bool Word_Description::add_defition_example(const std::string & def, const std::string & eg)
{
	if (definitions_examples.size() < (int)Max_Amount::definitions)
	{
		definitions_examples.push_back(std::make_pair(def, eg));
		return true;
	}
	return false;
}

bool Word_Description::add_sentence(const std::string & sentc)
{
	if (sentences.size() < (int)Max_Amount::sentences)
	{
		sentences.push_back(sentc);
		return true;
	}
	return false;
}
