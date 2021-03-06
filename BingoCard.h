//
// Created by gabrieltb on 5/5/22.
//

#ifndef BINGOCARD_H
#define BINGOCARD_H

#include "BingoGame.h"

class BingoGame; // Necessary forward declaration

class BingoCard
{
    private:
      unsigned int cardKeys[5][5]{};
      bool cardValues[5][5] = {
              {false, false, false, false, false},
              {false, false, false, false, false},
              {false, false, true,  false, false},
              {false, false, false, false, false},
              {false, false, false, false, false}};
      unsigned int columnTallies[5] = {0, 0, 1, 0, 0};
      unsigned int rowTallies[5] = {0, 0, 1, 0, 0};
      unsigned int diagonalTallies[2] = {1, 1}; // Element 0 is the top left diagonal
      unsigned int lastFoundKey[2]{};

      bool searchForKey(unsigned int);

    public:
      BingoCard(BingoGame *);
      explicit BingoCard(BingoGame *, const unsigned int[5][5]);
      
      void markValue(unsigned int);
      unsigned int getClearedLines() const;

      friend void printBingoCard(BingoCard &);
};

#endif //BINGOCARD_H