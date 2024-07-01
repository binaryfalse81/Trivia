#include "game_better.h"
#include <iostream>

using namespace std;

GameBetter::GameBetter() : currentPlayer{ 0 }, playerCnt{ 0 }
{
    for (int i = 0; i < MAX_PLAYER_CNT; i++)
    {
        aPlayers[i] = new Player{"", 0, 0, false};
    }

    for (int i = 0; i < 50; i++)
    {
        popQuestions.push_back(createPopQuestion(i));
        scienceQuestions.push_back(createScienceQuestion(i));
        sportsQuestions.push_back(createSportQuestion(i));
        rockQuestions.push_back(createRockQuestion(i));
    }
}

GameBetter::~GameBetter()
{
    for (int i = 0; i < MAX_PLAYER_CNT; i++)
    {
        delete(aPlayers[i]);
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
    aPlayers[playerCnt]->setName(playerName);
    aPlayers[playerCnt]->setPlaces(0);
    aPlayers[playerCnt]->setPurses(0);
    aPlayers[playerCnt]->setInPenaltyBox(false);
    playerCnt++;

    cout << playerName << " was added" << endl;
    cout << "They are player number " << playerCnt << endl;
    return true;
}

void GameBetter::rolling(int roll)
{
    string name = GetCurPlayer()->getName();
    cout << name << " is the current player" << endl;
    cout << "They have rolled a " << roll << endl;

    if (GetCurPlayer()->getInPenaltyBox())
    {
        if (IsEven(roll))
        {
            cout << name << " is not getting out of the penalty box" << endl;
            return;
        }
        else
        {
            GetCurPlayer()->setInPenaltyBox(false);
            cout << name << " is getting out of the penalty box" << endl;
        }
    }

    GetCurPlayer()->setPlaces(GetCurPlayer()->getPlaces() + roll);
    if (GetCurPlayer()->getPlaces() > 11)
    {
        GetCurPlayer()->setPlaces(GetCurPlayer()->getPlaces() - 12);
    }
    cout << GetCurPlayer()->getName() << "'s new location is " << GetCurPlayer()->getPlaces() << endl;
    cout << "The category is " << currentCategory() << endl;

    askQuestion();
}

Player* GameBetter::GetCurPlayer()
{
    return aPlayers[currentPlayer];
}

bool GameBetter::IsEven(int roll)
{
    return (roll % 2 == 0);
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

    if (false == GetCurPlayer()->getInPenaltyBox())
    {
        cout << "Answer was correct!!!!" << endl;
        GetCurPlayer()->increasePurses();
        cout << GetCurPlayer()->getName() << " now has "
            << GetCurPlayer()->getPurses() << " Gold Coins." << endl;

        ret =  didPlayerWin();
    }

    increaseCurPlayer();
    return ret;
}

void GameBetter::increaseCurPlayer()
{
    currentPlayer++;
    if (currentPlayer == playerCnt)
    {
        currentPlayer = 0;
    }
}

bool GameBetter::wrongAnswer()
{
    if (false == GetCurPlayer()->getInPenaltyBox())
    {
        cout << "Question was incorrectly answered" << endl;
        cout << GetCurPlayer()->getName() + " was sent to the penalty box" << endl;
        GetCurPlayer()->setInPenaltyBox(true);
    }
    
    increaseCurPlayer();
    return true;
}

bool GameBetter::didPlayerWin(void)
{
    return !(GetCurPlayer()->getPurses() == MAX_COIN_CNT);
}