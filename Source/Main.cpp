#include "WordFactory.h"
#include "DatabaseImpl.h"
#include "FileAccessImpl.h"

#include <iostream>

int main()
{
    FileAccessImpl fa;
    std::shared_ptr<Database> db = std::make_shared<DatabaseImpl>(DatabaseImpl{fa});
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
