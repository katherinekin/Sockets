#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include <iostream>
#include <sys/wait.h>
#include "WalshCode.h"

using namespace std;

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

//Reading input text file 
    int pid, count = 0, m = 0;
    //char *dest, *val, *c;
    int dest, val;
    bzero(buffer, 256);
    char newBuf[5];
        
//For each line read, forks a child process
//Each child creates a socket to connect to the server
//First set the port number and socket file descripter
    while(cin>>dest && cin>>val)
    {
      count++;

      if ((pid=fork())==0)
      {
        
    //Get val and dest, child prints its message
    //    if ( (c = strrchr(buffer, '\n')))
    //        *c = '\0';

    //    dest = strtok(buffer, " ");
    //    val = strtok(NULL, " ");

    //Set port and sock file descriptor
        portno = atoi(argv[2]);
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) 
           error("ERROR opening socket");
        server = gethostbyname(argv[1]);
        if (server == NULL) {
           fprintf(stderr,"ERROR, no such host\n");
           exit(0);
        }

    //Set destination variables
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
              server->h_length);
        serv_addr.sin_port = htons(portno);

        printf("Child %d, sending value: %d to child process %d\n", count, val, dest);
    //connect to server
        if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
            error("ERROR connecting");
    
    //Set a new buffer before sending over
    //count is child process number
        m = sprintf(newBuf, "%d %d %d",count, dest, val);
    //send to server
        n = write(sockfd,newBuf,5);
    
    
        if (n < 0) 
           error("ERROR writing to socket");
        break;
      }
      sleep(1);
    }

//END WHILE LOOP
    bzero(buffer, 256);
//If parent process, don't continue until all children are finished
    if (pid != 0)
    {
        wait(NULL);
        return 0;
    }

    n = read(sockfd,buffer,255);
    if (n < 0) 
        error("ERROR reading from socket");
    char *signal, *code;
    signal = strtok(buffer, "\n");
    code = strtok(NULL, "\n");

    WalshCode wc;
    int newVal = 0;
    vector<int> signalVect, codeVect;
    signalVect = wc.toVect(signal);
    codeVect = wc.toVect(code);

    newVal = wc.decode(signalVect, codeVect);
    printf("\nChild %d\nSignal: %s\nCode: %s\nReceived value = %d\n", count, signal, code, newVal);
    sleep(2);

    return 0;
}
