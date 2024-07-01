#pragma once

#include <string>
using namespace std;

class IGame
{
public:
    virtual bool add(string playerName) = 0;
    virtual void rolling(int roll) = 0;
    virtual bool wasCorrectlyAnswered() = 0;
    virtual bool wrongAnswer() = 0;
};
