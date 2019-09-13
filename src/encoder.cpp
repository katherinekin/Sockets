// A simple server in the internet domain using TCP
// The port nu1mber is passed as an argument

// Please note this is a C program
// It compiles without warnings with gcc

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>  //FD_SET, FD_ZERO
#include <netinet/in.h>

#include "WalshCode.h"
#include <vector>

#include<iostream>
using namespace std;

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen, client_socket[3];
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     //set of socket descriptors
     //fd_set readfds;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
//create the socket
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));

//type of socket created
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

//bind socket to given port
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     int count = 0;
     char *child, *dest, *val, *c, *endptr;
     //stores order of destinations to retrieve appropriate code
     int dest_order[3];
     long int childLong, destLong, valLong;
     
     WalshCode wc;
     vector<int> signal;

     bzero(buffer, 256);
     while (count < 3)
     {
        
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *)&clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");
        
        n = read(newsockfd,buffer,255);
     
        if (n < 0) 
            error("ERROR reading from socket");
//Remove last newline character from buffer
        if ( (c = strrchr(buffer, '\n')))
            *c = '\0';
        child = strtok(buffer," ");
        dest = strtok(NULL, " ");
        val = strtok(NULL, " ");
//store the child socket fd in the container client_socket
        childLong = strtol(child, &endptr, 10);
        client_socket[childLong-1] = newsockfd;
//store the destination in the container dest_order
        destLong = strtol(dest, &endptr, 10);
        dest_order[destLong-1] = childLong;
        valLong = strtol(val, &endptr, 10);
        printf("Here is the message from child %d: Value = %s, Destination = %s\n",
            ++count, val, dest);
        bzero(buffer,256);
        usleep(1000000);
    
        //Calculate EM with each iteration, Signal = wc.encode(val, child)
        if (signal.size() == 0)
            signal = wc.encode(valLong, childLong);
        else
            signal = wc.encode(valLong, childLong, signal);
     }
     char newBuf[256];
     bzero(buffer, 256);     
     string s;
     for(int i = 0; i < 3; i++)
     {
        bzero(newBuf,256);
        //m = sprintf(newBuf, "Child %d receives code from %d\n", i+1, dest_order[i]);
        s = wc.toString(signal)+"\n"+wc.toString(wc.getCode(dest_order[i]));
        for(int j = 0; j < s.length(); j++)
            newBuf[j] = s[j];
        n = write(client_socket[i], newBuf, strlen(newBuf));
        if (n < 0) 
             error("ERROR writing to socket");
        sleep(1);
     }
     //n = write(newsockfd, "Hello again\n", 12);
     return 0; 
}
