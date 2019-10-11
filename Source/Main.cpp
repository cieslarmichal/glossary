#include "WordFactory.h"
#include "WordsDatabase.h"
#include "FileAccessImpl.h"
#include "MemoryStorage.h"

#include <iostream>

int main()
{
    FileAccessImpl fa;
    MemoryStorage storage;
    std::shared_ptr<Database> db = std::make_shared<WordsDatabase>(WordsDatabase{fa, storage});
    WordFactory factory{db};
    auto word = factory.createWord({"voice","glos"});
    if(word)
    {
        std::cout<< *word;
    }
    else
    {
        std::cerr<<"ERROR";
    }

	return 0;
}
