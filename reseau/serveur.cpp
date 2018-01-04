/*
g++ -c serveur.cpp
g++ serveur.o -o serveur -lsfml-network -lsfml-system
*/

#include <SFML/Network.hpp>
#include <iostream>

int main()
{
  unsigned int port = 12345;

  // Create a socket to receive a message from anyone
  sf::UdpSocket socket;

  // Listen to messages on the specified port
  if (socket.bind(port) != sf::Socket::Done)
      return EXIT_FAILURE;
  std::cout << "Server is listening to port " << port << ", waiting for a message... " << std::endl;

  // Wait for a message
  char in[128];
  std::size_t received;
  sf::IpAddress sender;
  unsigned short senderPort;
  if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
      return EXIT_FAILURE;
  std::cout << "Message received from client " << sender << ": \"" << in << "\"" << std::endl;

  // Send an answer to the client
  const char out[] = "Hi, I'm the server";
  if (socket.send(out, sizeof(out), sender, senderPort) != sf::Socket::Done)
      return EXIT_FAILURE;
  std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;

    return EXIT_SUCCESS;
}
