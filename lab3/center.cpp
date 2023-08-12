#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    char message[1024];
    char sourceHost[3]; // Assuming the host names are h1, h2, h3, h4

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return -1;
    }

    // Set up the server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8888);

    // Bind the socket to the server address
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind the socket." << std::endl;
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Failed to listen for connections." << std::endl;
        return -1;
    }

    std::cout << "Waiting for connections..." << std::endl;

    // Accept incoming connections
    socklen_t clientAddressSize = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize);
    if (clientSocket == -1) {
        std::cerr << "Failed to accept the connection." << std::endl;
        return -1;
    }

    // Get the source host from the client's IP address
    std::string clientIP = inet_ntoa(clientAddress.sin_addr);
    std::string sourceHostClient = clientIP.substr(clientIP.length() - 1);

    std::cout << "Connected with " << sourceHostClient << std::endl;

    while (true) {
        // Receive message from the client
        memset(message, 0, sizeof(message));
        ssize_t bytesRead = recv(clientSocket, message, sizeof(message), 0);
        if (bytesRead == -1) {
            std::cerr << "Failed to receive data." << std::endl;
            break;
        } else if (bytesRead == 0) {
            // Connection closed by the client
            std::cout << "Connection closed by the client." << std::endl;
            break;
        }

        // Prepend the source host to the message
        std::string modifiedMessage = sourceHostClient + std::string(":") + std::string(message);

        // Forward the message to h5 (assuming h5's IP is "10.0.0.5")
        int h5Socket = socket(AF_INET, SOCK_STREAM, 0);
        if (h5Socket == -1) {
            std::cerr << "Failed to create socket." << std::endl;
            break;
        }

        struct sockaddr_in h5Address;
        h5Address.sin_family = AF_INET;
        h5Address.sin_addr.s_addr = inet_addr("10.0.0.5");
        h5Address.sin_port = htons(8888);

        if (connect(h5Socket, (struct sockaddr *)&h5Address, sizeof(h5Address)) == -1) {
            std::cerr << "Failed to connect to h5." << std::endl;
                        std::cerr << "Failed to connect to h5." << std::endl;
            break;
        }

        ssize_t bytesSent = send(h5Socket, modifiedMessage.c_str(), modifiedMessage.length(), 0);
        if (bytesSent == -1) {
            std::cerr << "Failed to send data to h5." << std::endl;
            break;
        }

        // Close the socket to h5
        close(h5Socket);
    }

    // Close the client socket
    close(clientSocket);

    // Close the server socket
    close(serverSocket);

    return 0;
}