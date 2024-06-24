#include "html_message.h"
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

#define SERVER_IP "127.0.0.1"
#define PORT 8888

int main(int argc, char const *argv[]) {
  int clientSocket;
  if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    cerr << "Socket creation failed" << endl;
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  if (inet_pton(AF_INET, SERVER_IP, &serverAddress.sin_addr) <= 0) {
    cerr << "Invalid address/ Address not supported" << endl;
    exit(EXIT_FAILURE);
  }

  if (connect(clientSocket, (struct sockaddr *)&serverAddress,
              sizeof(serverAddress)) < 0) {
    cerr << "Connection failed" << endl;
    exit(EXIT_FAILURE);
  }

  char *message = new char[argc];
  for (int i = 1; i < argc; i++) {
    strcat(message, argv[i]);
    strcat(message, " ");
  }

  HTML html;
  strcpy(html.content, message);
  strcpy(html.tag, "p");
  strcpy(html.id, "1");

  if (send(clientSocket, &html, sizeof(html), 0) != sizeof(html)) {
    std::cerr << "Send failed" << std::endl;
    exit(EXIT_FAILURE);
  }

  char buffer[1024 * 1024];
  string response;

  if (recv(clientSocket, buffer, 1024 * 1024, 0) < 0) {
    std::cerr << "Receive failed" << std::endl;
    exit(EXIT_FAILURE);
  }

  response = buffer;

  cout << response << endl;

  close(clientSocket);

  return 0;
}
