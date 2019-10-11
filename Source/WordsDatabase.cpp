#include "WordsDatabase.h"

#include "StringHelper.h"

namespace
{
const std::string wordDescriptionsFilePath{"../database/words.txt"};
const std::string definitionMark{":"};
const std::string exampleMark{"//"};
const std::string sentenceMark{"\""};
}

WordsDatabase::WordsDatabase(FileAccess &access, Storage& storageInit) : fileAccess(access), storage{storageInit}
{
}

boost::optional<WordDescription> WordsDatabase::getWordDescription(const EnglishWord &englishWord) const
{
    //Word deserializer
    auto glossaryContent = fileAccess.readContent(wordDescriptionsFilePath);
    auto startIndex = glossaryContent.find(englishWord +"\n{\n");
    if(startIndex==std::string::npos)
    {
        return boost::none;
    }
    auto endIndex = glossaryContent.find("}");

    auto lines = stringHelper::getSplitLines(stringHelper::substring(glossaryContent, startIndex, endIndex));
    return wordDescriptionParser.parse(lines);
}

void WordsDatabase::saveWord(const EnglishWordWithDescription &word) const
{
    //WordSerializer
    std::string toFile =  word.englishWord + "\n{\n";
    toFile+=word.wordDescription.toString() + "}\n";
    fileAccess.append(wordDescriptionsFilePath, toFile);
}
