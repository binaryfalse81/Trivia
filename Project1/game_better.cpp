#include "game_better.h"
#include <iostream>

using namespace std;

GameBetter::GameBetter() : currentPlayer{ 0 }, places{}, purses{}
{
    for (int i = 0; i < 50; i++) {
        string str1 = "Pop Question " + to_string(i);
        popQuestions.push_back(str1);

        string str2 = "Science Question " + to_string(i);
        scienceQuestions.push_back(str2);

        string str3 = "Sports Question " + to_string(i);
        sportsQuestions.push_back(str3);

        rockQuestions.push_back(createRockQuestion(i));
    }
}

string GameBetter::createRockQuestion(int index)
{
    string indexStr = "Rock Question " + to_string(index);
    return indexStr;
}

bool GameBetter::isPlayable()
{
    return (howManyPlayers() >= 2);
}

bool GameBetter::add(string playerName)
{
    players.push_back(playerName);
    places[howManyPlayers() - 1] = 0;
    purses[howManyPlayers() - 1] = 0;
    inPenaltyBox[howManyPlayers() - 1] = false;

    cout << playerName << " was added" << endl;
    cout << "They are player number " << players.size() << endl;
    return true;
}

int GameBetter::howManyPlayers()
{
    return (int)players.size();
}

void GameBetter::rolling(int roll)
{
    cout << players[currentPlayer] << " is the current player" << endl;
    cout << "They have rolled a " << roll << endl;

    if (inPenaltyBox[currentPlayer])
    {
        if (roll % 2 != 0)
        {
            isGettingOutOfPenaltyBox = true;

            cout << players[currentPlayer] << " is getting out of the penalty box" << endl;
            places[currentPlayer] = places[currentPlayer] + roll;
            if (places[currentPlayer] > 11) places[currentPlayer] = places[currentPlayer] - 12;

            cout << players[currentPlayer] << "'s new location is " << places[currentPlayer] << endl;
            cout << "The category is " << currentCategory() << endl;
            askQuestion();
        }
        else
        {
            cout << players[currentPlayer] << " is not getting out of the penalty box" << endl;
            isGettingOutOfPenaltyBox = false;
        }

    }
    else
    {
        places[currentPlayer] = places[currentPlayer] + roll;
        if (places[currentPlayer] > 11) places[currentPlayer] = places[currentPlayer] - 12;

        cout << players[currentPlayer] << "'s new location is " << places[currentPlayer] << endl;
        cout << "The category is " << currentCategory() << endl;
        askQuestion();
    }
}

void GameBetter::askQuestion()
{
    if (currentCategory() == "Pop")
    {
        cout << popQuestions.front() << endl;
        popQuestions.pop_front();
    }

    if (currentCategory() == "Science")
    {
        cout << scienceQuestions.front() << endl;
        scienceQuestions.pop_front();
    }

    if (currentCategory() == "Sports")
    {
        cout << sportsQuestions.front() << endl;
        sportsQuestions.pop_front();
    }

    if (currentCategory() == "Rock")
    {
        cout << rockQuestions.front() << endl;
        rockQuestions.pop_front();
    }
}

string GameBetter::currentCategory()
{
    if (places[currentPlayer] == 0) return "Pop";
    if (places[currentPlayer] == 4) return "Pop";
    if (places[currentPlayer] == 8) return "Pop";
    if (places[currentPlayer] == 1) return "Science";
    if (places[currentPlayer] == 5) return "Science";
    if (places[currentPlayer] == 9) return "Science";
    if (places[currentPlayer] == 2) return "Sports";
    if (places[currentPlayer] == 6) return "Sports";
    if (places[currentPlayer] == 10) return "Sports";
    return "Rock";
}

bool GameBetter::wasCorrectlyAnswered()
{
    if (inPenaltyBox[currentPlayer])
    {
        if (isGettingOutOfPenaltyBox)
        {
            inPenaltyBox[currentPlayer] = false;
            cout << "Answer was correct!!!!" << endl;

            purses[currentPlayer]++;
            cout << players[currentPlayer] << " now has "
                << purses[currentPlayer] << " Gold Coins." << endl;

            bool winner = didPlayerWin();
            currentPlayer++;
            if (currentPlayer == players.size()) currentPlayer = 0;

            return winner;
        }
        else
        {
            currentPlayer++;
            if (currentPlayer == players.size()) currentPlayer = 0;
            return true;
        }
    }
    else
    {
        cout << "Answer was correct!!!!" << endl;

        purses[currentPlayer]++;
        cout << players[currentPlayer] << " now has "
            << purses[currentPlayer] << " Gold Coins." << endl;

        bool winner = didPlayerWin();
        currentPlayer++;
        if (currentPlayer == players.size()) currentPlayer = 0;

        return winner;
    }
}

bool GameBetter::wrongAnswer()
{
    if (inPenaltyBox[currentPlayer])
    {
        if (isGettingOutOfPenaltyBox)
        {
            cout << "Question was incorrectly answered" << endl;
            cout << players[currentPlayer] + " was sent to the penalty box" << endl;
            inPenaltyBox[currentPlayer] = true;

            currentPlayer++;
            if (currentPlayer == players.size()) currentPlayer = 0;
            return true;
        }
        else
        {
            currentPlayer++;
            if (currentPlayer == players.size()) currentPlayer = 0;
            return true;
        }
    }
    else
    {
        cout << "Question was incorrectly answered" << endl;
        cout << players[currentPlayer] + " was sent to the penalty box" << endl;
        inPenaltyBox[currentPlayer] = true;

        currentPlayer++;
        if (currentPlayer == players.size()) currentPlayer = 0;
        return true;
    }
}

bool GameBetter::didPlayerWin()
{
    return !(purses[currentPlayer] == 6);
}