#include "DictionaryObserverService.h"

#include <memory>

#include "gtest/gtest.h"

#include "DictionaryObserverMock.h"

using namespace ::testing;
using namespace glossary::dictionary;

class DictionaryObserverServiceTest : public Test
{
public:
    std::vector<std::string> englishWords{"englishWord1", "englishWord2"};
    std::shared_ptr<DictionaryObserverMock> observer1 =
        std::make_shared<StrictMock<DictionaryObserverMock>>();
    std::shared_ptr<DictionaryObserverMock> observer2 =
        std::make_shared<StrictMock<DictionaryObserverMock>>();
    DictionaryObserverService dictionaryObserverService;
};

TEST_F(DictionaryObserverServiceTest, givenRegisteredObserver_shouldNotifyObserverAboutChanges)
{
    dictionaryObserverService.registerObserver(observer1.get());
    EXPECT_CALL(*observer1, update(englishWords));

    dictionaryObserverService.notifyObservers(englishWords);
}

TEST_F(DictionaryObserverServiceTest, givenRegisteredObservers_shouldNotifyObserversAboutChanges)
{
    dictionaryObserverService.registerObserver(observer1.get());
    dictionaryObserverService.registerObserver(observer2.get());
    EXPECT_CALL(*observer1, update(englishWords));
    EXPECT_CALL(*observer2, update(englishWords));

    dictionaryObserverService.notifyObservers(englishWords);
}

TEST_F(DictionaryObserverServiceTest, givenRemovedObserver_shouldNotNotifyObserverAboutChanges)
{
    dictionaryObserverService.registerObserver(observer1.get());
    dictionaryObserverService.removeObserver(observer1.get());

    dictionaryObserverService.notifyObservers(englishWords);
}

TEST_F(DictionaryObserverServiceTest, givenRemovedObservers_shouldNotNotifyObserversAboutChanges)
{
    dictionaryObserverService.registerObserver(observer1.get());
    dictionaryObserverService.registerObserver(observer2.get());
    dictionaryObserverService.removeObserver(observer1.get());
    dictionaryObserverService.removeObserver(observer2.get());

    dictionaryObserverService.notifyObservers(englishWords);
}

TEST_F(DictionaryObserverServiceTest, givenRemovedOneObserverFromTwo_shouldNotNotifyOneObserverAboutChanges)
{
    dictionaryObserverService.registerObserver(observer1.get());
    dictionaryObserverService.registerObserver(observer2.get());
    dictionaryObserverService.removeObserver(observer2.get());
    EXPECT_CALL(*observer1, update(englishWords));

    dictionaryObserverService.notifyObservers(englishWords);
}