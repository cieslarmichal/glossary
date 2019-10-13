#pragma once

class AnswerCounter
{
public:
    virtual ~AnswerCounter() = default;

    virtual void addCorrectAnswer() const = 0;
    virtual void addIncorrectAnswer() const = 0;
};