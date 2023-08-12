#include <iostream>

#include <string.h>

#include <sys/socket.h>

#include <arpa/inet.h>

#include <unistd.h>

#include <thread>

#include <map>

#include <set>



const int PORT = 8000;

std::map<int,int> id2usr;

std::set<int> socket_set;



void handleClient(int client_socket,int order) {

    std::string message;

    char buffer[1024] = {0};

    ssize_t valread;



    while ((valread = read(client_socket, buffer, 1024)) > 0) {

        message = std::string(buffer, valread);

        std::cout << "Message received: " << message<<" From h"<< order << std::endl;

        if(message[0] != 'T' || message[1] != 'o' || message[2] != ' ' || message[3] != 'h' ){

            std::cout << "Format Error"  << std::endl; 

            continue;

        }

        int aim = int(message[4]) - 48;

        buffer[4] = '0' + order;

        send(id2usr[aim], buffer, valread, 0);

        memset(buffer, 0, sizeof(buffer));

        

    }

    close(client_socket);



}



int main() {

    int server_fd, new_socket;

    struct sockaddr_in address;

    int addrlen = sizeof(address);

    int opt = 1;



    // Create socket

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {

        perror("socket");

        exit(EXIT_FAILURE);

    }



    // Set socket options

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {

        perror("setsockopt");

        exit(EXIT_FAILURE);

    }



    address.sin_family = AF_INET;

    address.sin_addr.s_addr = INADDR_ANY;

    address.sin_port = htons(PORT);



    // Bind socket

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {

        perror("bind");

        exit(EXIT_FAILURE);

    }



    // Listen for connections

    if (listen(server_fd, 5) < 0) {

        perror("listen");

        exit(EXIT_FAILURE);

    }



    std::cout << "Server is listening on port " << PORT << std::endl;



    while (true) {

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {

            perror("accept");

            exit(EXIT_FAILURE);

        }



        

        int order = int(inet_ntoa(address.sin_addr)[7]) -48;

        if (socket_set.count(order)){

            continue;

        }



        socket_set.insert(order);

        std::cout<<"h"<<order<<" connected" << std::endl;

        id2usr[order] = new_socket;

        std::thread clientThread(handleClient, new_socket,order);

        clientThread.detach();

    }



    close(server_fd);



    return 0;

}

