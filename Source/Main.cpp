#include "WordFactory.h"
#include "DatabaseImpl.h"
#include "FileAccessImpl.h"
#include "StorageImpl.h"

#include <iostream>

int main()
{
    FileAccessImpl fa;
    StorageImpl storage;
    std::shared_ptr<Database> db = std::make_shared<DatabaseImpl>(DatabaseImpl{fa, storage});
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
