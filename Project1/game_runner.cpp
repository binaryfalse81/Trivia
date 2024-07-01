#include "game.h"

int main()
{
    bool notAWinner;

    Game aGame;

    aGame.add("Chet");
    aGame.add("Pat");
    aGame.add("Sue");

    do
    {
        int roll = rand() % 6 + 1;

        aGame.rolling(roll);

        if (rand() % 9 == 7)
        {
            notAWinner = aGame.wrongAnswer();
        }
        else
        {
            notAWinner = aGame.wasCorrectlyAnswered();
        }
    } while (notAWinner);
}