#include "BoardGame.h"
#include "Random.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>

namespace BoardGame {

  constexpr std::string_view PADDING{
    "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
  }; //PADDING

  Board::Board() {
    for (uint i = 0; i < 16; ++i) {
      board_array[i] = i + 1;
    }
    board_array[15] = 0;
  } //constructor()

  uint& Board::access(uint x, uint y) {
    assert(x < 4);
    assert(y < 4);
    return board_array[x * 4 + y];
  } //access()

  uint Board::access(uint x, uint y) const {
    assert(x < 4);
    assert(y < 4);
    return board_array[x * 4 + y];
  } //access() const

  void Board::printToConsole() const {
    std::cout << PADDING;
    for (uint i = 0; i < 4; ++i) {
      for (uint j = 0; j < 4; ++j) {
        if (access(i, j) > 9) std::cout << " [" << access(i, j) << "]";
        else if (access(i,j) == 0) std::cout << " [  ]";
        else std::cout << " [ " << access(i, j) << "]";
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  } //printToConsole()

  bool Board::isWinning() const {
    for (uint i = 0; i < 15; i++) {
      if (board_array[i] != (i + 1)) return false;
    }
    return true;
  } //isWinning()

  void Board::processInput(Input i) {
    uint ni = getNullIndex();
    uint ni_x = ni / 4;
    uint ni_y = ni % 4;
    switch (i) {
      case DOWN:        
        if (ni_x >= 1) swapValues(access(ni_x, ni_y), access(ni_x - 1, ni_y));
        break;
      case UP:
        if (ni_x < 3) swapValues(access(ni_x, ni_y), access(ni_x +1, ni_y));
        break;
      case RIGHT:
        if (ni_y >= 1) swapValues(access(ni_x, ni_y), access(ni_x, ni_y - 1));
        break;
      case LEFT:
        if (ni_y < 3) swapValues(access(ni_x, ni_y), access(ni_x, ni_y + 1));
        break;
      default:
        break;
    }
  } //processInput()

  uint Board::getNullIndex() const{
    for (uint i = 0; i < 16; ++i) {
      if (board_array[i] == 0) return i;
    }
  } //getNullIndex()

  void Board::swapValues(uint& i1, uint& i2) {
    uint v1 = i1;
    uint v2 = i2;
    i1 = v2;
    i2 = v1;
  } //swapValues()

  std::istream& operator>>(std::istream& is, Input& i) {
    char c{};
    loop:
    std::cout << "WASD to move, Q to quit: ";
    is >> c;
    switch (c) {
      case 'W': case 'w':
        i = UP;
        break;
      case 'A': case 'a':
        i = LEFT;
        break;
      case 'S': case 's':
        i = DOWN;
        break;
      case 'D': case 'd':
        i = RIGHT;
        break;
      case 'Q': case 'q':
        i = QUIT;
        break;
      default:
        std::cout << "Invalid Input.\n";
        goto loop;
    }
    is.clear();
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
  } //operator>>(Input)

  void Board::randomize() {
    Input in;
    for (uint i = 0; i < 100000; ++i) {
      in = (Input)Random::get(0, 3);
      processInput(in);
    }
  } //randomize()

} //namespace BoardGame