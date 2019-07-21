#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Txt_File
{
public:
	/**
	* Class parametrized constructor
	* @param string containing path to txt file
	*/
	Txt_File(const std::string &);

	/**
	* Reads content of txt file and saves into container
	* @return vector of strings containing separated lines
	*/
	std::vector<std::string> get_lines();

	/**
	* Appends given string to the end of the txt file
	* @param string with data to write
	*/
	void write(const std::string &);

	/**
	* Friend overloaded operator, appends string to the end of txt file
	* @param string with data to write
	*/
	Txt_File & operator<<(const std::string &);

private:
	std::unique_ptr<std::fstream> file;

	std::string access_path;

	bool open();

	void close();
};


