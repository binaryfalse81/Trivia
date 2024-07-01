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
    Player(string name)
        : name{ name }, places{ 0 }, coin{ 0 }, isJail{ false } { }
    void setPlaces(int places)
    {
        this->places = places;
    }
    void increaseCoin(void)
    {
        this->coin++;
        cout << "Answer was correct!!!!" << endl;
        cout << name << " now has "
            << coin << " Gold Coins." << endl;
    }
    void enterJail(void)
    {
        this->isJail = true;
        cout << "Question was incorrectly answered" << endl;
        cout << name + " was sent to the penalty box" << endl;
    }
    void exitJail(void)
    {
        this->isJail = false;
    }

    string getName(void)
    {
        return this->name;
    }
    int getPlaces(void)
    {
        return this->places;
    }
    void moveNextPlace(int nextRoll)
    {
        places += nextRoll;
        if (places > 11)
        {
            places -= 12;
        }
        cout << name << "'s new location is " << places << endl;
    }
    int getCoin(void)
    {
        return this->coin;
    }
    bool isInJail(void)
    {
        return this->isJail;
    }

private:
    string name;
    int places;
    int coin;
    bool isJail;
};

class GameBetter : public IGame
{
public:
    GameBetter();
    bool add(string playerName);
    void rolling(int roll);
    bool wasCorrectlyAnswered(void);
    bool wrongAnswer(void);

private:
    vector<Player*> users;
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