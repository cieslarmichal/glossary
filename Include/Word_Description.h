#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class Word_Description
{
public:
	/**
	* Class default constructor
	* Creates empty instance to append data later
	*/
	Word_Description();

	/**
	* Class parametrized constructor
	* Takes strings then splits them to the respective containers
	* @param vector of strings with labeled data
	* from HTML_Parser::filter_lines(const std::string &)
	*/
	Word_Description(std::vector<std::string> &);

	/**
	* Class copy constructor
	* @param other object of Word_Description class 
	*/
	Word_Description(const Word_Description &);

	/**
	* Adds sentence to the container
	* @param string containing sentence
	* @return if addition ended successfully or not
	*/
	bool add_sentence(const std::string &);

	/**
	* Adds definition and example to the container
	* @param def	string containing definition
	* @param eg		string containing example
	* @return if addition ended successfully or not
	*/
	bool add_defition_example(const std::string & def, const std::string & eg);

	/**
	* Returns vector of definitions and examples
	* @return vector of pairs of strings, 
	* containing respectively definition and example
	*/
	std::vector<std::pair<std::string, std::string>> get_definitions_examples() const;

	/**
	* Returns vector of sentences
	* @return vector of strings containing sentences
	*/
	std::vector<std::string> get_sentences() const;

private:
	std::vector<std::pair<std::string, std::string>> definitions_examples;

	std::vector<std::string> sentences;

	enum class Max_Amount { sentences = 5, definitions = 7 };

	static const std::vector<std::string> key_words;
private:
	void split_input(const std::vector<std::string> &);

	void clean_input(std::vector<std::string> &);
};


