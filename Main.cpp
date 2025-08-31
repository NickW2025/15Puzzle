#include "BoardGame.h"

#include <iostream>

int main() {
  using namespace BoardGame;

  Board board{};
  board.randomize();

  //game loop
  while (true) {
    board.printToConsole();

    Input i;
    std::cin >> i;
    if (i == QUIT) break;
    board.processInput(i);

    if (board.isWinning()) {
      board.printToConsole();
      std::cout << "Congratulations! You Win!\n";
      break;
    }
  }

  return 0;
} //main()