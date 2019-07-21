#pragma once
#include <algorithm> 


namespace String_Additives
{
	// trim from start (in place)
	static inline void ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			[](unsigned char c) {return !isspace(c); }));
	}

	// trim from end (in place)
	static inline void rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(),
			[](unsigned char c) {return !isspace(c); }).base(), s.end());
	}

	// trim from both ends (in place)
	static inline void trim(std::string &s) {
		ltrim(s);
		rtrim(s);
	}

	// trim from start (copying)
	static inline std::string ltrim_copy(std::string s) {
		ltrim(s);
		return s;
	}

	// trim from end (copying)
	static inline std::string rtrim_copy(std::string s) {
		rtrim(s);
		return s;
	}

	// cuts string into string: <0,start_position) + (end_position,std::string::size())
	static inline std::string cut_off_string(const std::string & line, size_t start_position, size_t end_position)
	{
		std::string str1{ line }, str2{ line };

		if (start_position > line.size() - 1)
		{
			throw "cut_off_string: wrong start_position";
		}

		if (str2.size() - end_position < 0)
		{
			throw "cut_off_string: wrong end_position";
		}
		str1 = str1.substr(0, start_position);
		str2 = str2.substr(end_position + 1, str2.size() - end_position);

		return (str1 + str2);
	}
}

//std::string HTML_Parser::remove_spaces(const std::string & line)
//{
//	std::string cleared_line{ line };
//	size_t space_position = -1;
//	size_t index = 0;
//	size_t size_to_cut = 0;
//
//	for (index = 0; index < cleared_line.size(); ++index)
//	{
//		if (isspace(cleared_line.at(index)))
//		{
//			if (size_to_cut == 0)
//			{
//				space_position = index;
//			}
//			size_to_cut++;
//		}
//		else if ((size_to_cut > 1) && (space_position != -1))
//		{
//			if (space_position == 0)
//			{
//				cleared_line = cut_off_string(cleared_line, space_position, space_position + size_to_cut - 1);
//			}
//			else
//			{
//				cleared_line = cut_off_string(cleared_line, space_position + 1, space_position + size_to_cut - 1);
//			}
//			index = -1;
//			size_to_cut = 0;
//			space_position = -1;
//		}
//		else
//		{
//			space_position = -1;
//			size_to_cut = 0;
//		}
//	}
//
//	return cleared_line;
//}