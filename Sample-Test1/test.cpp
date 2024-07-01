#include "pch.h"
#include "../Project1/game.cpp"
#include "../Project1/game_better.cpp"
#include "../Project1/IGame.h"
#include "../Project1/game.h"
#include "../Project1/game_better.h"

class ParameterizedTestFixture : public testing::TestWithParam<int>
{
public:
    string playGame(IGame& aGame, int seed)
    {
        std::ostringstream oss;
        auto oldCoutStreamBuf = cout.rdbuf();
        cout.rdbuf(oss.rdbuf());

        bool notAWinner;

        aGame.add("Chet");
        aGame.add("Pat");
        aGame.add("Sue");

        srand(seed);

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

        cout.rdbuf(oldCoutStreamBuf);
        return oss.str();
    }
};

INSTANTIATE_TEST_CASE_P
(
    goldenMaster,
    ParameterizedTestFixture,
    testing::Values(1, 50, 100, 777)
);

TEST_P(ParameterizedTestFixture, goldenMaster)
{
    int seed = GetParam();
    Game game_origin;
    GameBetter game_refactor;

    string expected = playGame(game_origin, seed);
    string actual = playGame(game_refactor, seed);

    EXPECT_EQ(expected, actual);
}