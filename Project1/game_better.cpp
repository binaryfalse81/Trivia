#include "game_better.h"
#include <iostream>

using namespace std;

GameBetter::GameBetter() : currentPlayer{ 0 }
{
    for (int i = 0; i < 50; i++)
    {
        popQuestions.push_back(createPopQuestion(i));
        scienceQuestions.push_back(createScienceQuestion(i));
        sportsQuestions.push_back(createSportQuestion(i));
        rockQuestions.push_back(createRockQuestion(i));
    }
}

string GameBetter::createPopQuestion(int index)
{
    string indexStr = "Pop Question " + to_string(index);
    return indexStr;
}

string GameBetter::createScienceQuestion(int index)
{
    string indexStr = "Science Question " + to_string(index);
    return indexStr;
}

string GameBetter::createSportQuestion(int index)
{
    string indexStr = "Sports Question " + to_string(index);
    return indexStr;
}

string GameBetter::createRockQuestion(int index)
{
    string indexStr = "Rock Question " + to_string(index);
    return indexStr;
}

bool GameBetter::add(string playerName)
{
    users.push_back(new Player(playerName));

    cout << playerName << " was added" << endl;
    cout << "They are player number " << users.size() << endl;
    return true;
}

void GameBetter::rolling(int roll)
{
    string name = GetCurPlayer()->getName();
    cout << name << " is the current player" << endl;
    cout << "They have rolled a " << roll << endl;

    if (GetCurPlayer()->isInJail())
    {
        if (IsEven(roll))
        {
            cout << name << " is not getting out of the penalty box" << endl;
            return;
        }
        else
        {
            cout << name << " is getting out of the penalty box" << endl;
            GetCurPlayer()->exitJail();
        }
    }

    GetCurPlayer()->moveNextPlace(roll);

    cout << "The category is " << currentCategory() << endl;

    askQuestion();
}

Player* GameBetter::GetCurPlayer()
{
    return users[currentPlayer];
}

bool GameBetter::IsEven(int roll)
{
    return (roll % 2 == 0); // commit test
}

void GameBetter::askQuestion(void)
{
    string strCurCategory = currentCategory();

    if (strCurCategory == Category::POP)
    {
        cout << popQuestions.front() << endl;
        popQuestions.pop_front();
    }
    else if (strCurCategory == Category::SCIENCE)
    {
        cout << scienceQuestions.front() << endl;
        scienceQuestions.pop_front();
    }
    else if (strCurCategory == Category::SPORTS)
    {
        cout << sportsQuestions.front() << endl;
        sportsQuestions.pop_front();
    }
    else
    {
        cout << rockQuestions.front() << endl;
        rockQuestions.pop_front();
    }
}

string GameBetter::currentCategory(void)
{
    int mod = GetCurPlayer()->getPlaces() % MAX_CATEGORY_CNT;
    switch (mod)
    {
    case 0:
        return Category::POP;
    case 1:
        return Category::SCIENCE;
    case 2:
        return Category::SPORTS;
    }

    return Category::ROCK;
}

bool GameBetter::wasCorrectlyAnswered()
{
    bool ret = true;

    if (false == GetCurPlayer()->isInJail())
    {
        GetCurPlayer()->increaseCoin();
        ret =  didPlayerWin();
    }

    increaseCurPlayer();
    return ret;
}

void GameBetter::increaseCurPlayer()
{
    currentPlayer++;
    if (currentPlayer == users.size())
    {
        currentPlayer = 0;
    }
}

bool GameBetter::wrongAnswer()
{
    if (false == GetCurPlayer()->isInJail())
    {
        GetCurPlayer()->enterJail();
    }
    
    increaseCurPlayer();
    return true;
}

bool GameBetter::didPlayerWin(void)
{
    return !(GetCurPlayer()->getCoin() == MAX_COIN_CNT);
}