#include "ThreadSafeQueue.h"

#include <thread>

#include "gtest/gtest.h"

#include "testDirectory/testVariables/TestStrings.h"

using namespace ::testing;
using namespace utils;

namespace
{

void pushElements(const std::vector<std::string>& elementsToPush, ThreadSafeQueue<std::string>& queue)
{
    for (const auto& element : elementsToPush)
    {
        queue.push(element);
    }
}

void popElement(ThreadSafeQueue<std::string>& queue)
{
    while (not queue.empty())
    {
        queue.pop();
    }
}

void popFromOneQueueAndPushToOther(ThreadSafeQueue<std::string>& inputQueue,
                                   ThreadSafeQueue<std::string>& outputQueue)
{
    while (not inputQueue.empty())
    {
        if (const auto data = inputQueue.pop())
        {
            outputQueue.push(*data);
        }
    }
}
}

class ThreadSafeQueueTest : public Test
{
public:
    const std::string element1{"element1"};
    const std::string element2{"element2"};
    const std::string element3{"element3"};
    const std::vector<std::string> elements{element1, element2, element3};
};

TEST_F(ThreadSafeQueueTest, givenInitializedQueue_shouldBeEmpty)
{
    ThreadSafeQueue<std::string> queue;

    ASSERT_TRUE(queue.empty());
}

TEST_F(ThreadSafeQueueTest, givenInitializedQueueWithElements_shouldNotBeEmpty)
{
    ThreadSafeQueue<std::string> queueWithElements{elements};

    ASSERT_FALSE(queueWithElements.empty());
}

TEST_F(ThreadSafeQueueTest, popElements_shouldReturnAllElementsFromQueueAndQueueShouldBeEmpty)
{
    ThreadSafeQueue<std::string> queueWithElements{testStrings};

    const auto data = queueWithElements.popAll();

    ASSERT_EQ(data, testStrings);
    ASSERT_TRUE(queueWithElements.empty());
}

TEST_F(ThreadSafeQueueTest, pushElementToQueue_shouldReturnSameElementWithPop)
{
    ThreadSafeQueue<std::string> queue;

    queue.push(element1);

    const auto elementFromQueue = queue.pop();
    ASSERT_EQ(elementFromQueue, element1);
}

TEST_F(ThreadSafeQueueTest, pushElementsWithMultipleThreads_shouldNotDeadlock)
{
    ThreadSafeQueue<std::string> queue;

    std::thread t1(&pushElements, testStrings, std::ref(queue));
    std::thread t2(&pushElements, testStrings, std::ref(queue));
    std::thread t3(&pushElements, testStrings, std::ref(queue));
    t1.join();
    t2.join();
    t3.join();
}

TEST_F(ThreadSafeQueueTest, popElementsWithMultipleThreads_shouldNotDeadlock)
{
    ThreadSafeQueue<std::string> queueWithElements{testStrings};

    std::thread t1(&popElement, std::ref(queueWithElements));
    std::thread t2(&popElement, std::ref(queueWithElements));
    std::thread t3(&popElement, std::ref(queueWithElements));
    t1.join();
    t2.join();
    t3.join();
}

TEST_F(ThreadSafeQueueTest, popElementsFromOneQueueAndPushToOtherQueue_shouldNotDeadlock)
{
    ThreadSafeQueue<std::string> inputQueue{testStrings};
    ThreadSafeQueue<std::string> resultQueue{};

    std::thread t1(&popFromOneQueueAndPushToOther, std::ref(inputQueue), std::ref(resultQueue));
    std::thread t2(&popFromOneQueueAndPushToOther, std::ref(inputQueue), std::ref(resultQueue));
    std::thread t3(&popFromOneQueueAndPushToOther, std::ref(inputQueue), std::ref(resultQueue));
    t1.join();
    t2.join();
    t3.join();

    const auto resultData = resultQueue.popAll();
    ASSERT_EQ(resultData.size(), testStrings.size());
}