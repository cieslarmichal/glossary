#pragma once
#include "Word.h"

class Word_Viewer
{
public:
	/**
	* Class default constructor
	*/
	Word_Viewer();

	/**
	* Views incomplete description of the word
	* @param instance of Word class
	*/
	void view_short_description(const Word &);

	/**
	* Views full description of the word
	* @param instance of Word class
	*/
	void view_full_description(const Word &);
};

