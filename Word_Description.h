#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class Word_Description
{
public:
	Word_Description(std::vector<std::string>);
	std::vector<std::pair<std::string, std::string>> definitions_examples;
	std::vector<std::string> sentences;
private:
	void clean_input(std::vector<std::string> &);
	void split_input(const std::vector<std::string> &);
	bool add_defition_example(const std::string & def, const std::string & eg);
	bool add_sentence(const std::string & sentence);
	private:
	enum class Max_Amount { sentences = 2, definitions = 5 };
	static const std::vector<std::string> key_words;
};

