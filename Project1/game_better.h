#ifndef GAME_BETTER_H_
#define GAME_BETTER_H_

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "IGame.h"

using std::string;
using std::list;
using std::vector;

class GameBetter : public IGame
{
public:
    GameBetter();

    string createRockQuestion(int index);
    bool isPlayable();
    bool add(string playerName);

    int howManyPlayers();
    void rolling(int roll);

    bool wasCorrectlyAnswered();
    bool wrongAnswer();


private:
    vector<string> players;

    int places[6];
    int purses[6];

    bool inPenaltyBox[6];

    list<string> popQuestions;
    list<string> scienceQuestions;
    list<string> sportsQuestions;
    list<string> rockQuestions;

    int currentPlayer;
    bool isGettingOutOfPenaltyBox;

    void askQuestion();
    string currentCategory();
    bool didPlayerWin();
};

#endif /* GAME_BETTER_H_ */