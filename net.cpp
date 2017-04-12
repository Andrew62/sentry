//
//  net.cpp
//  Sentry
//
//  Created by Andrew Woizesko on 2/25/17.
//  Copyright © 2017 Andrew Woizesko. All rights reserved.
//

//socket stuffs
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "net.hpp"

using namespace net;

Socket::Socket(char* listenPort){
    this->listenPort = listenPort;
    
    // initialize the interface
    // don't care if IP4 or IP6
    struct addrinfo hints; // define our interface
    memset(&hints, 0, sizeof(hints)); // make sure the struct is empy
    hints.ai_family = AF_UNSPEC; // don't care if IP4 or IP6
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE; // fill in my IP for me
    
    // look up address info for this machine. Will populate service info
    if ((::getaddrinfo(NULL, this->listenPort, &hints, &this->serviceinfo)) == -1){
        this->errorExit(1, "getaddrinfor error ");
    }
    
    // make the socket file descriptor
    this->sock_fd = socket(this->serviceinfo->ai_family, this->serviceinfo->ai_socktype, this->serviceinfo->ai_protocol);
    
}

void Socket::errorExit(int exitCode, std::string msg){
    std::cout << msg << std::endl;
    exit(exitCode);
}

void Socket::bindSock(void){
    if ((::bind(this->sock_fd, this->serviceinfo->ai_addr, this->serviceinfo->ai_addrlen)) == -1){
        this->errorExit(1, "Failed to bind!");
    }
    
    // yes reuse socket
    int yes = 1;
    if ((::setsockopt(this->sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, this->serviceinfo->ai_addrlen)) == -1){
        this->errorExit(1, "setsockoprt");
    }
}

void Socket::startListening(int backlog){
    if ((::listen(this->sock_fd, backlog)) == -1){
        this->errorExit(1, "listen");
    }
}

void Socket::acceptData(struct sockaddr_storage their_addr) throw (int){
    socklen_t addr_size = sizeof(their_addr);
    int new_fd = ::accept(this->sock_fd, (struct sockaddr *)&their_addr, &addr_size);
    if (new_fd == -1){
        std::cout << "failed to get an accepting socket!" << std::endl;
        throw -1;
    }
    this->new_fd = new_fd;
}

void Socket::getData(void *buffer, int n_bytes, int flag){
    long success = ::recv(this->new_fd, buffer, n_bytes, flag);
    if (success == -1){
        this->errorExit(1, "Failed to receive data!");
    }
}

Socket::~Socket(void){
    ::freeaddrinfo(this->serviceinfo); // clear the linked list
    
    ::close(this->sock_fd);
    std::cout << "Socket closed" << std::endl;
}
