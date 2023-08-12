#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <thread>
#include <cstring>

const int PORT = 8000;


void sendMessage(int sock) {
    while (true) {      
        std::string message;
        std::cout << "Enter a message: "<<std::endl;
        std::getline(std::cin, message);
        
        if (message == "exit") {
            return;
        }
    send(sock, message.c_str(), message.size(), 0);
    std::cout << "Message sent: " << message << std::endl;
    }
}

void receiveMessage(int sock) {
    char buffer[1024] = {0};
    std::string message;
    int valread;
    while ((valread = read(sock, buffer, 1024)) > 0) {
        int order = int(buffer[4]) - 48 ;
        message = std::string(buffer, valread);
        std::cout <<"From h"<<order<<":"<< message.substr(5) << std::endl;

    }
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert address to binary
    if (inet_pton(AF_INET, "10.0.0.5", &serv_addr.sin_addr) <= 0) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    std::thread sendThread(sendMessage, sock);
    std::thread receiveThread(receiveMessage, sock);

    sendThread.join();
    receiveThread.join();

    close(sock);

    return 0;
}
