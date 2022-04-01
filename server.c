#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error (const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Usage ./server --portNo\n");
        exit(EXIT_FAILURE);
    }

    int sockfd, newsockfd, portno;
    char buffer[255];
    
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    portno = atoi(argv[1]); 

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        error("Error opening Socket");
    }
    bzero((char*)&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno); //Host to network shot
 
    
    if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 ) 
    {
        error("Binding Failed");
    }

    listen(sockfd, 3);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr,&clilen);
    if(newsockfd<0)
    {
        error("Error on Accept");
    }
    
    int i =1;
    while(i)
    {
        bzero(buffer, 255);
        int n = read(newsockfd, buffer, sizeof(buffer));
        if(n<0)
        {
            error("Error on reading");
        }
        printf("Client: %s\n", buffer);
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);

        n = write(newsockfd, buffer, strlen(buffer));
        if(n<0)
        {
            error("Error on writing");
        }
        i = strncmp("gorusuruz", buffer, 9);
    } 
    close(newsockfd);
    close(sockfd);
    exit(EXIT_SUCCESS);

}