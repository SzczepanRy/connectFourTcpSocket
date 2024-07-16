#include "board.hpp"
#include <algorithm>
#include <cerrno>
#include <iostream>
#include <string>
class Game : Board {

private:
  int getPosition() {

    int pos;
    std::cout << "please chose the  position";
    std::cin >> pos;

    return pos;
  }

public:
  char currentPlayer = '0';

  std::string GetStr(){
    return getBoardString();
 }

  bool makeMove(char player, int pos) {
    // idk if there should be a fer to a baord
    bool validPosition = validatePos(pos);

    if (!validPosition) {
      std::cout << "NOT A VALID POSITION\n";
      makeMove(player, pos);
    }

    bool placementSucessfull = placePiece(pos, player);

    if (!placementSucessfull) {
      std::cout << "DID NOT PLACE PIECE\n";
    }

    // placementSucessfull
    bool win = checkIfWon(player);
    if (win) {
      std::cout << "GAME WON BY " << player << '\n';
//      exit(1);
        return  true;
    }else{
        return false;
        }
  }
/*
  void gameLoop() {
    if (currentPlayer == '0') {
      makeMove(currentPlayer);
      currentPlayer = 'O';
    } else {
      makeMove(currentPlayer);
      currentPlayer = '0';
    }
    readBoard();
    gameLoop();
  }
*/
  Game() {
    Board board;
    //readBoard();
    //gameLoop();
  }
};

