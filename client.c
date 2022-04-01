#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> //for hostent

void error (const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int sockfd, n, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server; //Used to store info about given host

    
    FILE *file;
    file = fopen("textclone.txt", "a");

    char buffer[256];
    if(argc<3)
    {
        printf("Usage ./client --serverIpAdress --portNo\n");
        exit(EXIT_FAILURE);
    }
    
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        error("Error opening Socket");
    }

    server = gethostbyname(argv[1]);
    if(server == NULL)
    {
        printf("Error, no such host");
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server ->h_addr, (char*)&serv_addr.sin_addr.s_addr, server -> h_length);
    serv_addr.sin_port = htons(portno);
    if(connect(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        error("Connection Failed");
    }
    int i =1;
     while(i)
    {
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);
        
        int n = write(sockfd, buffer, strlen(buffer));
        fputs(buffer, file);

        if(n<0)
        {
            error("Error on writing");
        }
        
        bzero(buffer, 255);
        n = read(sockfd, buffer, sizeof(buffer));
        fputs(buffer, file);
        if(n<0)
        {
            error("Error on reading");
        }
        printf("Server: %s", buffer);

        i = strncmp("gorusuruz", buffer, 9);
        
    }

    fclose(file);
    close(sockfd);
    exit(EXIT_SUCCESS);



}