#pragma once

// TODO: Interface to 3 databases

namespace wordsDb
{

class WordsDb
{
public:
    virtual ~WordsDb() = default;

    // getTranslation
    // getTranslations
    // addTranslation
    // removeTranslation maybe????

    //    virtual void addCorrectAnswer(const EnglishWord&) = 0;
    //    virtual void addIncorrectAnswer(const EnglishWord&) = 0;
    //    virtual boost::optional<AnswersStatisticsPerWord>
    //    getAnswersStatisticsPerWord(const EnglishWord&) const = 0;
    //    virtual AnswersStatistics getAnswersStatistics() const = 0;

    //    virtual void addWord(const Word&) const = 0;
    //    virtual boost::optional<Word> getWord(const EnglishWord&) const = 0;
    //    virtual bool contains(const EnglishWord&) const = 0; maybe ?????
};
}