#pragma once

#include "FormattedDictionary.h"
#include <string>
#include <sstream>

namespace glossary::gui::view
{
class FormattedDictionariesStorage
{
public:
    FormattedDictionariesStorage() = default;
    explicit FormattedDictionariesStorage(QList<FormattedDictionary>);

    void updateDictionaryWords(const QString& dictionaryName, const FormattedDictionaryWords& words);
    void updateDictionaries(const QList<FormattedDictionary>& dicts);
    QList<FormattedDictionary> getDictionaries() const;
    QStringList getDictionaryNames() const;
    FormattedDictionaryWords getDictionaryWords(const QString& dictionaryName) const;
    bool dictionariesAreEmpty() const;

private:
    QList<FormattedDictionary> dictionaries;
};

inline bool operator==(const FormattedDictionariesStorage& lhs, const FormattedDictionariesStorage& rhs)
{
    return lhs.getDictionaries() == rhs.getDictionaries();
}
}
