#pragma once
#include <random>

class Random
{
public:
	/**
	* Default constructor is inaccessible.
	*/
	Random() = delete;

	/**
	* Returns randomized number by Mersenne Twister
	* @param range_start	int with a start value included
	* @param range_end		int with an end value included
	* @return	int number within range <range_start;range_end>
	*/
	static int get_random_number(int range_start, int range_end);
private:
	static std::random_device rd;
	static std::mt19937 mt;
};

