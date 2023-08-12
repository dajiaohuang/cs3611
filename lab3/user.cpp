#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddress;
    char message[1024];

    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return -1;
    }

    // Set up the server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("10.0.0.5"); // Replace with the actual IP address of h5
    serverAddress.sin_port = htons(8888);

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to connect to the server." << std::endl;
        return -1;
    }

    std::cout << "Connected to the server." << std::endl;

    // Set up the file descriptors for select
    fd_set readSet;
    fd_set writeSet;
    FD_ZERO(&readSet);
    FD_ZERO(&writeSet);

    while (true) {
        // Clear the file descriptor sets
        FD_ZERO(&readSet);
        FD_ZERO(&writeSet);

        // Add the client socket to the read set
        FD_SET(clientSocket, &readSet);

        // Add stdin (0) to the read set
        FD_SET(0, &readSet);

        // Check if there is any data to be sent
        if (strlen(message) > 0) {
            FD_SET(clientSocket, &writeSet);
        }

        // Use select to wait for activity on the file descriptors
        int maxFd = std::max(clientSocket, 0) + 1;
        int activity = select(maxFd, &readSet, &writeSet, nullptr, nullptr);
        if (activity == -1) {
            std::cerr << "Error in select." << std::endl;
            break;
        }

        // Check if there is data to be read from the server
        if (FD_ISSET(clientSocket, &readSet)) {
            // Receive response from the server
            memset(message, 0, sizeof(message));
            ssize_t bytesRead = recv(clientSocket, message, sizeof(message), 0);
            if (bytesRead == -1) {
                std::cerr << "Failed to receive data." << std::endl;
                break;
            } else if (bytesRead == 0) {
                // Connection closed by the server
                std::cout << "Connection closed by the server." << std::endl;
                break;
            }

            // Display the received message
            std::cout << "Received message: " << message << std::endl;
        }

        // Check if there is data to be read from stdin
        if (FD_ISSET(0, &readSet)) {
            // Read the message from the user
            std::cout << "Enter message: ";
            std::cin.getline(message, sizeof(message));
        }

        // Check if there is data to be sent
        if (FD_ISSET(clientSocket, &writeSet)) {
            // Send the message to the server
            ssize_t bytesSent = send(clientSocket, message, strlen(message), 0);
            if (bytesSent == -1) {
            std::cerr << "Failed to send data." << std::endl;
            break;
            } else if (bytesSent == 0) {
            // Connection closed by the server
            std::cout << "Connection closed by the server." << std::endl;
            break;
        }

        // Clear the message buffer after sending
        memset(message, 0, sizeof(message));
    }
}

// Close the socket
close(clientSocket);

return 0;
}