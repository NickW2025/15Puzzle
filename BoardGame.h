#ifndef PUZZLE_BOARD_H
#define PUZZLE_BOARD_H

#include <cstddef>
#include <iostream>

namespace BoardGame {
  using uint = std::size_t;

  enum Input {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    QUIT,
  }; //enum Input

  std::istream& operator>>(std::istream&, Input&);

  class Board {
    private: //data members
      uint board_array[16]{};

    public: //constructors
      Board();

    public: //member functions
      void printToConsole() const;
      void processInput(Input);
      bool isWinning() const;
      uint& access(uint x, uint y);
      uint access(uint x, uint y) const;
      uint getNullIndex() const;
      void swapValues(uint&, uint&);
      void randomize();
  }; //class Board

} //namespace BoardGame

#endif