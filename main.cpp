/*
 * Gabriel Talbert Bunt & Marc Chagnon
 * CS 211
 * 2022-05-08
 * Description:
 * This program models a game of Bingo. Three classes are defined, BingoGame, BingoCard and Caller.
 * The BingoGame class requires a Caller and at least one BingoCard prior to playing a round.
 * Once these are initialized and associated with the BingoGame, the program runs through a game of Bingo:
 * the Caller generates the number for the round, passing it to BingoGame which then passes it to each
 * Bingo Card associated with the instance of the game. The BingoCard searches its array of values (the card),
 * and if it contains the number generated by the Caller, "marks" the card.
 * Each round, the BingoGame prints every card and checks if any of the cards are a winner. If so, the game ends.
 * Otherwise, the program continues to the subsequent round until every valid number has been generated by the
 * Caller (1-75, inclusive).
 * Finally, the program will identify the winning BingoCards by printing them. The program also prints the numbers
 * called by the Caller.
 *
 * /--------------------------------------------\
 * | Test Data:                                 ||
 * |--------------------------------------------|/
 * |~BingoCard test                             |
 * |                                            |
 * |-USING:                                     |
 * | testmain()                                 |
 * |                                            |
 * |-INPUT:                                     |
 * | {1,  2,  3,  4,  5 },                      |
 * | {16, 18, 20, 22, 24},                      |
 * | {31, 34, 37, 40, 43},                      |
 * | {50, 51, 56, 57, 60},                      |
 * | {61, 65, 67, 69, 75}                       |
 * |                                            |
 * |                                            |
 * |-OUTPUT: (Numbers prefixed with R are red)  |
 * |  B   I   N   G   O                         |
 * |  1   16  31  50  61                        |
 * |  2   18  34  51  65                        |
 * |  3   20 R0   56  67                        |
 * |  4   22  40  57  69                        |
 * |  5   24  43  60  75                        |
 * |                                            |
 * |-PASSED? Yes                                |
 * |--------------------------------------------|
 * |~BingoGame test                             |
 * |                                            |
 * |-USING:                                     |
 * | testmain()                                 |
 * |                                            |
 * |-INPUT:                                     |
 * | {1, 2, . . . 74, 75}                       |
 * |                                            |
 * |-OUTPUT: (Numbers prefixed with R are red)  |
 * | Winner! (5 rounds)                         |
 * |  B   I   N   G   O                         |
 * | R1   16  31  50  61                        |
 * | R2   18  34  51  65                        |
 * | R3   20 R0   56  67                        |
 * | R4   22  40  57  69                        |
 * | R5   24  43  60  75                        |
 * | Numbers called: 1 2 3 4 5                  |
 * |                                            |
 * |-PASSED? Yes                                |
 * |--------------------------------------------|
 * |~Random game test                           |
 * |                                            |
 * |-USING:                                     |
 * | main()                                     |
 * |                                            |
 * |-INPUT:                                     |
 * | N/A                                        |
 * |                                            |
 * |-OUTPUT: (Numbers prefixed with R are red)  |
 * | Winner! (45 rounds)                        |
 * |  B   I   N   G   O                         |
 * | R7  R16 R31 R47  61                        |
 * |  8   19 R36 R49 R67                        |
 * |  9  R22 R0  R52  68                        |
 * |  11  25 R43 R54  72                        |
 * | R15  28  44 R60 R74                        |
 * | Numbers called: 53 63 21 64 3 10 59 15 58  |
 * | 7 32 46 69 16 6 70 35 22 4 71 23 43 14 36  |
 * | 41 67 52 60 56 24 54 40 17 51 31 12 13 18  |
 * | 47 74 55 33 75 42 49                       |
 * |                                            |\
 * |-PASSED? Yes                                ||
 * \--------------------------------------------/
*/

#include <iostream>
#include <iomanip>
#include "BingoGame.h"
#include "BingoCard.h"
#include "Caller.h"

using namespace std;

int testMain();

int main()
{
    /* uncomment to test
    return testMain();
    
    */

    // variable definitions
    int numBingoCards;
    int gameRound;
    int numWinners;

    cout << "\n generating Bingo Game.";
    BingoGame game1 = BingoGame();
    cout << "\n generating caller.";
    Caller caller1 = Caller(&game1);

    cout << "\nThis game will have three players, each with one Bingo card.";
    BingoCard bcard1(&game1);
    BingoCard bcard2(&game1);
    BingoCard bcard3(&game1);

    numWinners = 0;
    for (gameRound = 1; gameRound < 76; gameRound++)
    {
        cout << "\nRound " << gameRound << "! Caller's number is.... ";
        game1.playRound();
        cout << game1.getCurrentRoundValue() << "!";
        cout << "\nCheck those Bingo Cards:" << endl;
        displayBingoCardsInGame(&game1, false);
        cout << endl;
        numWinners = game1.checkForWin();
        if (numWinners > 0) gameRound = 76;
    }

    if (numWinners > 0)
    {
        cout << "\nWe have ";
        if (numWinners == 1)
        {
            cout << "a winner! Here is the winning card:\n";
        } else
        {
            cout << numWinners << " winners! Here are the winning cards:\n";
        }
        displayBingoCardsInGame(&game1, true);
    } else
    {
        cout << "\nUnforunately, there were no winners.";
    }
    cout << "\nHere are the numbers called by the Caller:" << endl;
    displayNumbersCalled(&caller1);

    return 0;
}

// function to handle printing each individual BingoCard.
void printBingoCard(BingoCard &card)
{
    string RED_BACKGROUND_CODE = "\033[48;2;255;0;0m";
    string NORMAL_CODE = "\033[0m";
    string UNDERLINE_CODE = "\033[4m";
    cout << UNDERLINE_CODE << " B  I  N  G  O " << NORMAL_CODE << endl;
    for (unsigned int row = 0; row < 5; row++)
    {
        for (unsigned int column = 0; column < 5; column++)
        {
            if (card.cardValues[column][row])
            {
                cout << RED_BACKGROUND_CODE;
            }
            cout << " " << left << setw(2) << card.cardKeys[column][row] << NORMAL_CODE;
        }
        cout << endl;
    }
}

// function to handle printing all BingoCards (iterates over BingoGame's cardsInPlay member)
void displayBingoCardsInGame(BingoGame *bGame, bool displayWinnersOnly)
{
    if (displayWinnersOnly)
    {
        for (BingoCard *g: bGame->cardsInPlay)
        {
            if (g->getClearedLines() > 0)
            {
                cout << "\n";
                printBingoCard(*g);
            }
        }
    } else
    {
        for (BingoCard *g: bGame->cardsInPlay)
        {
            cout << "\n";
            printBingoCard(*g);
        }
    }
}

void displayNumbersCalled(Caller *callerPtr)
{
    for (int i = 0; i < Caller::ARR_SIZE; i++)
    {
        if (callerPtr->numsCalledArr[i] != 0)
        {
            cout << callerPtr->numsCalledArr[i] << " ";
        } else
        {
            i = Caller::ARR_SIZE;
        }
    }
}

// A testing version of main
int testMain()
{
    // variable definitions
    int numBingoCards;
    int gameRound;
    int numWinners;

    cout << "\n generating Bingo Game.";
    BingoGame game1 = BingoGame();
    cout << "\n generating caller.";
    Caller caller1 = Caller(&game1, true);

    unsigned int testArray[5][5] = {
            {1,  2,  3,  4,  5},
            {16, 18, 20, 22, 24},
            {31, 34, 37, 40, 43},
            {50, 51, 56, 57, 60},
            {61, 65, 67, 69, 75}
    };
    cout << "\nThis test will have one players with one Bingo card.";
    BingoCard bcard1(&game1, testArray);

    numWinners = 0;
    for (gameRound = 1; gameRound < 76; gameRound++)
    {
        cout << "\nRound " << gameRound << "! Caller's number is.... ";
        game1.playRound();
        cout << game1.getCurrentRoundValue() << "!";
        cout << "\nCheck those Bingo Cards:" << endl;
        displayBingoCardsInGame(&game1, false);
        cout << endl;
        numWinners = game1.checkForWin();
        if (numWinners > 0) gameRound = 76;
    }

    if (numWinners > 0)
    {
        cout << "\nWe have ";
        if (numWinners == 1)
        {
            cout << "a winner! Here is the winning card:\n";
        } else
        {
            cout << numWinners << " winners! Here are the winning cards:\n";
        }
        displayBingoCardsInGame(&game1, true);
    } else
    {
        cout << "\nUnforunately, there were no winners.";
    }
    cout << "\nHere are the numbers called by the Caller:" << endl;
    displayNumbersCalled(&caller1);

    return 0;
}