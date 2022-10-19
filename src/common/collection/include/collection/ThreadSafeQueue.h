#pragma once

#include <mutex>
#include <optional>
#include <queue>
#include <vector>

namespace common::collection
{
template <typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue() = default;

    explicit ThreadSafeQueue(const std::vector<T>& elements)
    {
        for (const auto& element : elements)
        {
            queue.push(element);
        }
    }

    void push(const T& data)
    {
        std::lock_guard<std::mutex> guard(lock);
        queue.push(data);
    }

    void push(const T&& data)
    {
        std::lock_guard<std::mutex> guard(lock);
        queue.push(data);
    }

    std::optional<T> pop()
    {
        std::lock_guard<std::mutex> guard(lock);
        if (not queue.empty())
        {
            const auto data = queue.front();
            queue.pop();
            return std::move(data);
        }
        return std::nullopt;
    }

    std::vector<T> popAll()
    {
        std::vector<T> data;
        while (not empty())
        {
            if (const auto element = pop())
            {
                data.emplace_back(*element);
            }
        }
        return data;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> guard(lock);
        return queue.empty();
    }

private:
    std::queue<T> queue;
    mutable std::mutex lock;
};
}