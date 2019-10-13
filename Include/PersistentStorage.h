#pragma once

#include "Storage.h"
#include "MemoryStorage.h"
#include "FileAccess.h"
#include "WordsSerializer.h"
#include <memory>

class PersistentStorage : public Storage
{
public:
    PersistentStorage(std::shared_ptr<const FileAccess>, std::shared_ptr<const WordsSerializer>);

    void addWord(const Word &) override;
    boost::optional<Word> getWord(const EnglishWord &) const override;
    Words getWords() const override;
    Words::size_type size() const override;
    bool empty() const override;
    Words::const_iterator begin() const override;
    Words::const_iterator end() const override;

private:
    void loadFile();
    void serialize();

    std::shared_ptr<const FileAccess> fileAccess;
    std::shared_ptr<const WordsSerializer> serializer;
    MemoryStorage storage;

    static const std::string fileDirectory;
    static const std::string fileName;
    static const std::string filePath;
};