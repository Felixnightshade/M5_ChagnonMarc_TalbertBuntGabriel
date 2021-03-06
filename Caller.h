#ifndef CALLER_H
#define CALLER_H

class BingoGame;

class Caller
{
    private:
      BingoGame *bingoGamePtr;                       // Used for communicating with associated BingoGame
      static const int ARR_SIZE = 75;                // A Bingo Game will always have max 75 rounds by definition of the game
      int numsCalledArr[ARR_SIZE]{};                 // To track the numbers called by the caller
      int numsCalledCounter;                         // Counter to track the round
      bool usePregeneratedNumbers = false;
      unsigned int pregeneratedNumbers[75]{};

    public:
      explicit Caller(BingoGame *);          // Constructor with BingoGame parameter
      Caller(BingoGame *,
             bool);                          // Constructor that gives predetermined numbers. Mostly for testing.
      void generateCurrentRoundValue();      // Caller generates current round value (between 1,75 inclusive)
      void setCurrentRoundValue();           // Assigns current round value to BingoGame
      void
      assignCallerToBingoGame();             // Function to associate Caller object with BingoGame object, run in constructor
      friend void displayNumbersCalled(
              Caller *);                     // Friend function allowing main program to display elements in Caller's prviate member numsCalledArr.
};

#endif