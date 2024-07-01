#ifndef GAME_BETTER_H_
#define GAME_BETTER_H_

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "IGame.h"

using namespace std;

const int MAX_CATEGORY_CNT = 4;
const int MAX_COIN_CNT = 6;
const int MAX_PLAYER_CNT = 6;

namespace Category
{
    const string POP = "Pop";
    const string SCIENCE = "Science";
    const string SPORTS = "Sports";
    const string ROCK = "Rock";
}

class Player
{
public:
    Player(string name, int places, int purses, bool inPenaltyBox)
        : name{ name }, places{ places }, purses{ purses }, inPenaltyBox{ inPenaltyBox } { }
    void setName(string name)
    {
        this->name = name;
    }
    void setPlaces(int places)
    {
        this->places = places;
    }
    void setPurses(int purses)
    {
        this->purses = purses;
    }
    void increasePurses(void)
    {
        this->purses++;
    }
    void setInPenaltyBox(bool inPenaltyBox)
    {
        this->inPenaltyBox = inPenaltyBox;
    }

    string getName(void)
    {
        return this->name;
    }
    int getPlaces(void)
    {
        return this->places;
    }
    int getPurses(void)
    {
        return this->purses;
    }
    bool getInPenaltyBox(void)
    {
        return this->inPenaltyBox;
    }

private:
    string name;
    int places;
    int purses;
    bool inPenaltyBox;
};

class GameBetter : public IGame
{
public:
    GameBetter();
    ~GameBetter();
    bool add(string playerName);
    void rolling(int roll);
    bool wasCorrectlyAnswered(void);
    bool wrongAnswer(void);

private:
    Player* aPlayers[MAX_PLAYER_CNT];
    int playerCnt;
    int currentPlayer;

    list<string> popQuestions;
    list<string> scienceQuestions;
    list<string> sportsQuestions;
    list<string> rockQuestions;

    string createPopQuestion(int index);
    string createScienceQuestion(int index);
    string createSportQuestion(int index);
    string createRockQuestion(int index);

    Player* GetCurPlayer(void);
    void increaseCurPlayer(void);
    bool IsEven(int roll);
    void askQuestion(void);
    string currentCategory(void);
    bool didPlayerWin(void);
};

#endif /* GAME_BETTER_H_ */