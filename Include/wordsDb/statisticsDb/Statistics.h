#pragma once

#include <map>

#include "AnswersStatisticsPerWord.h"

namespace wordsDb::statisticsDb
{
using AnswersStatistics = std::map<EnglishWord, AnswersStatisticsPerWord>;
}
