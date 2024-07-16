#include "game.hpp"
#include <arpa/inet.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sstream>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

class Server : Game {

private:
  int listeningSocket;
  int clientSocket;

  char currentPlayer = '0';

  static void err(string err) { cerr << err << endl; }

  void bindSocket() {
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(6060);

    inet_pton(this->listeningSocket, "0.0.0.0", &hint.sin_addr);

    if (bind(this->listeningSocket, (sockaddr *)&hint, sizeof(hint)) == -1) {
      err("could not bind the ip/port");
    }
  }
  void startListen() {
    if (listen(this->listeningSocket, SOMAXCONN) == -1) {
      err("could not start listening on locket " +
          to_string(this->listeningSocket));
    }
  }
  void acceptCall() {
    sockaddr_in client;
    socklen_t clinetSize;
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    this->clientSocket =
        accept(this->listeningSocket, (sockaddr *)&client, &clinetSize);

    memset(host, 0, NI_MAXHOST);
    memset(serv, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr *)&client, sizeof(client), host,
                             NI_MAXHOST, serv, NI_MAXSERV, 0);

    if (result == 0) {
      cout << host << " connected to " << serv << endl;
    } else {
      inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
      cout << host << " connected to " << ntohs(client.sin_port) << endl;
    }
  }

  void receveLoop() {

    char buff[4096]; // whats the importance of the buffer size

    while (true) {
      memset(buff, 0, 4096);

      int bytesReceved = recv(this->clientSocket, buff, 4096, 0);

      if (bytesReceved == -1) {
        err("issue receving bytes");
        return;
      }
      if (bytesReceved == 0) {
        cout << "the client disconnected";
        return;
      }

      // dislay message
      cout << " message : " << string(buff, 0, bytesReceved) << endl;

      std::string recevedString = string(buff, 0, bytesReceved);

      int pos = stoi(recevedString);

      if (currentPlayer == '0') {
        bool win = makeMove(currentPlayer, pos);
        if (win) {
          char mess[] = "player 0 won";
          send(this->clientSocket, &mess, sizeof(mess), 0);
        } else {
          std::string str = GetStr();
          std::cout << " BOARD " << str << " END\n";
          char strBuff[sizeof(str) + 1];
          strcpy(strBuff, str.c_str());

          char *buff = &str[0];

          send(this->clientSocket, &strBuff, sizeof(str) + 74, 0);
          char mess[] = "input coords 0-6: ";
          send(this->clientSocket, &mess, sizeof(mess), 0);
        }
        currentPlayer = 'O';
      } else {
        bool win = makeMove(currentPlayer, pos);
        if (win) {
          char mess[] = "player O won";
          send(this->clientSocket, &mess, sizeof(mess), 0);
        } else {
          std::string str = GetStr();
          std::cout << " BOARD " << str << " END\n";
          char strBuff[sizeof(str) + 1];
          strcpy(strBuff, str.c_str());

          char *buff = &str[0];

          send(this->clientSocket, &strBuff, sizeof(str) + 74, 0);
          char mess[] = "input coords 0-6: ";
          send(this->clientSocket, &mess, sizeof(mess), 0);
        }
        currentPlayer = '0';
      }
      // resend the message
      // send(this->clientSocket, buff, bytesReceved + 1, 0);
      // const string str = "<html> <h1> " + string(buff, 0, bytesReceved) +
      // "</h1> </html>";
    }
  }

public:
  Server() {
    // create server
    this->listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->listeningSocket == -1)
      err("could not create socket");
    // bind ip/port
    bindSocket();
    // make the socket listen for a clinet
    startListen();
    // accept clinet call
    acceptCall();
    // close listening socket when client connection accepted
    close(this->listeningSocket);
    // receve data form clinet

    receveLoop();
    // close connection to clinet
    close(this->clientSocket);
  }
};

int main() {

  Server init;

  return 0;
}
