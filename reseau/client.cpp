/*
g++ -c client.cpp
g++ client.o -o client -lsfml-network -lsfml-system
*/

#include <SFML/Network.hpp>
#include <iostream>

int main()
{
    unsigned int port = 12345;

    // Ask for the server address
    sf::IpAddress server;
    do
    {
        std::cout << "Type the address or name of the server to connect to: ";
        std::cin  >> server;
    }
    while (server == sf::IpAddress::None);

    // Create a socket for communicating with the server
    sf::UdpSocket socket;

    // Send a message to the server
    const char out[] = "Hi, I'm a client";
    if (socket.send(out, sizeof(out), server, port) != sf::Socket::Done)
        return EXIT_FAILURE;
    std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;

    // Receive an answer from anyone (but most likely from the server)
    char in[128];
    std::size_t received;
    sf::IpAddress sender;
    unsigned short senderPort;
    if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
        return EXIT_FAILURE;
    std::cout << "Message received from " << sender << ": \"" << in << "\"" << std::endl;

    return EXIT_SUCCESS;
}
