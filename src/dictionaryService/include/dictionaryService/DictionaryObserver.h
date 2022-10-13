#pragma once



namespace glossary::dictionaryService
{
class DictionaryObserver
{
public:
    virtual ~DictionaryObserver() = default;

    virtual void update(const EnglishWords&) = 0;
};
}