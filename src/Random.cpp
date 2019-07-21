#include "Random.h"

std::random_device Random::rd;
std::mt19937 Random::mt(rd());


int Random::get_random_number(int range_start, int range_end)
{
	std::uniform_int_distribution<int> dist(range_start, range_end);
	return dist(mt);
}

