//
//  net.hpp
//  Sentry
//
//  Created by Andrew Woizesko on 2/25/17.
//  Copyright © 2017 Andrew Woizesko. All rights reserved.
//

#ifndef net_hpp
#define net_hpp

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>


namespace net {
    class Socket{
        public:
            // bind to a file descriptor
            void bindSock(void);
        
            // start accepting data
            void acceptData(struct sockaddr_storage their_addr) throw (int);
        
            // start listening on a port
            void startListening(int backlog);
        
            // actually receive data
            void getData(void *buffer, int n_bytes, int flag);
        
            // simple constructor
            Socket(char* listenPort);
            ~Socket(void); 
        private:
            struct addrinfo *serviceinfo;
        
            // initial socket descriptor
            int sock_fd;
        
            // file descriptor where we'll read data from 
            int new_fd;
            char* listenPort;
        
            // convenience funciton to quit if something goes wrong with
            // any of the socket operations
            void errorExit(int exitCode, std::string msg);
    };
}

#endif /* net_hpp */
