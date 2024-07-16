#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <string>
class Board {

private:
  char board[6][7];
  char input;
  void fillBoard() {
    for (auto &row : this->board) {
      for (auto &col : row) {
        col = '_';
      }
    }
  }

  bool checkSpaceForPos(int pos) {
    if (this->board[0][pos] != '_') {
      return false;
    }
    return true;
  }
  std::string convertToString(char *a, int size) {
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
      s = s + a[i];
    }
    return s;
  }

public:
  void readBoard() {
    system("clear");

    for (int x = 0; x < 7; x++) {
      std::cout << x << ',';
    }
    std::cout << '\n';

    for (auto &row : this->board) {
      for (auto &col : row) {
        std::cout << col << ',';
      }
      std::cout << '\n';
    }
  }
  std::string getBoardString() {
    char charArr[105];

    std::string str = "";
    std::cout << "READING\n";
    int currentIndex = 0;
    /*
for (int x = 0; x < 7; x++) {
  charArr[currentIndex] = x;
  currentIndex++;
  charArr[currentIndex] = ',';
  currentIndex++;
}
charArr[currentIndex] = '\n';
currentIndex++;

for (auto &row : this->board) {
  for (auto &col : row) {
    charArr[currentIndex] = col;
    currentIndex++;
    charArr[currentIndex] = ',';
    currentIndex++;
  }
  charArr[currentIndex] = '\n';
  currentIndex++;
}
*/
    for (int x = 0; x < 7; x++) {
      str = str + std::to_string(x);
      str = str + ',';
    }
    str = str +'\n';
    for (auto &row : this->board) {
      for (auto &col : row) {
        str = str + col;
        str = str +',';
      }
      str = str +'\n';
    }

    for (int i = 0; i < 105; i++) {

      //    std::cout <<charArr[i] ;
    }

   // std::string s(charArr);
   // std::cout << "str " << str << '\n';
    return str;
  }

  bool validatePos(int pos) {
    if (pos > -1 && pos < 7 && this->checkSpaceForPos(pos)) {
      return true;
    }
    return false;
  }
  bool placePiece(int pos, char player) {
    for (int i = 5; i >= 0; i--) {
      if (board[i][pos] == '_') {
        board[i][pos] = player;
        return true;
      }
    }
    return false;
  }

  bool checkIfWon(char player) {
    bool vert = false;
    vert = checkVertical(player);
    bool horiz = false;
    horiz = checkHorizontal(player);
    bool LSlant = false;
    LSlant = checkLeftSlant(player);
    bool RSlant = false;
    RSlant = checkRightSlant(player);

    std::cout << vert << horiz << RSlant << LSlant << '\n';
    if (vert || horiz || RSlant || LSlant) {

      readBoard();
      return true;
    }

    return false;
  }

  bool checkVertical(char player) {
    int win = 0;
    for (int i = 0; i < 7; i++) {
      for (int j = 0; j < 6; j++) {
        if (board[j][i] == player) {
          win++;
          if (win == 4) {
            return true;
          }

        } else {
          win = 0;
        }
      }
      win = 0;
    }
    return false;
  }

  bool checkHorizontal(char player) {
    int win = 0;
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 7; j++) {
        if (board[i][j] == player) {
          win++;
          if (win == 4) {
            return true;
          }

        } else {
          win = 0;
        }
      }
      win = 0;
    }
    if (win == 4) {
      return true;
    } else {
      return false;
    }
  }

  bool checkRightSlant(char player) {
    int win = 0;
    for (int i = 3; i < 7; i++) {
      for (int j = 0; j < 3; j++) {
        for (int x = 0; x < 4; x++) {
          if (board[j + x][i - x] == player) {
            win++;
            if (win == 4) {
              return true;
            }

          } else {
            win = 0;
          }
        }
        win = 0;
      }
    }
    return false;
  }
  bool checkLeftSlant(char player) {
    int win = 0;

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 3; j++) {
        for (int x = 0; x < 4; x++) {
          if (board[j + x][i + x] == player) {
            win++;
            if (win == 4) {
              return true;
            }

          } else {
            win = 0;
          }
        }
        win = 0;
      }
    }

    return false;
  }

  Board() { fillBoard(); }
};
