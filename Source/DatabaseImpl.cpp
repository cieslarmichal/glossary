#include "DatabaseImpl.h"

#include "StringHelper.h"
#include <iostream>

namespace
{
const std::string wordDescriptionsFilePath{"../database/glossary.txt"};
const std::string definitionMark{":"};
const std::string exampleMark{"//"};
const std::string sentenceMark{"\""};
}

DatabaseImpl::DatabaseImpl(FileAccess &access, Storage<EnglishWord, Word>& storageInit) : fileAccess(access), storage{storageInit}
{
}

boost::optional<WordDescription> DatabaseImpl::getWordDescription(const EnglishWord &englishWord) const
{
    //Word deserializer
    std::string glossaryContent = fileAccess.readContent(wordDescriptionsFilePath);

    auto startIndex = glossaryContent.find(englishWord +"\n{\n");
    if(startIndex==std::string::npos)
    {
        return boost::none;
    }
    auto endIndex = glossaryContent.find("}");

    auto lines = stringHelper::getSplitLines(stringHelper::substring(glossaryContent, startIndex, endIndex));
    return wordDescriptionParser.parse(lines);
}

void DatabaseImpl::writeWordWithDescription(const EnglishWordWithDescription &word) const
{
    //WordSerializer
    std::string toFile =  word.englishWord + "\n{\n";
    toFile+=word.wordDescription.toString() + "}\n";
    fileAccess.append(wordDescriptionsFilePath, toFile);
}
