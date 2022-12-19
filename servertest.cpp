#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstdio>
#include <arpa/inet.h>

//PORT 2000
/*void error(const char* msg)
{
    (void) msg;
    perror("error");
    exit(1);
}*/
int main(int ac, char **av)
{
    int portNo;//port serveur (2000)
    //socklen_t cliLen;//taille addr client pour accept()
    int addrlen;
    int n;//retour read() write()
    char buffer[256];//pour lire le message depuis la socket
    struct sockaddr_in serv_addr;//est une structure contenant une adresse internet. Cette structure est définie dans netinet/in.h.
    //struct sockaddr_in cli_addr;

    fd_set readfds;
    int     max_clients = 2;
    int     client_socket[2];
    int sockfd;//retour socket() server
    int newSockfd;//retour socket() client
    int max_sd;
    int sd;
    int activity;

    //clear/init fdset
    FD_ZERO(&readfds);

    if(ac < 2)
    {
        std::cerr << "ERR0R, no port" << std::endl;
        exit(1);
    }
    //initialize client ocket
    for (int i = 0 ; i < max_clients ; i++)
        client_socket[i] = 0;

    //create socket (master socket)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int reuseaddr_on = 1;
    if( setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR,
            &reuseaddr_on, sizeof( reuseaddr_on)) < 0)
        std::cout << "Error sockopt" << std::endl;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portNo = atoi(av[1]);
    serv_addr.sin_family = AF_INET;//si communication iternet utlise cette variable sinon AF_UNIX en local
    serv_addr.sin_port = htons(portNo);//converti le port number en network byte order
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//contient l'IP de l'hote
    //lie la socket du serveur avec son addr
    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        std::cerr << "ERROR on binding" << std::endl;
    //ecoute la socket du serveur et definie le nb de connection en attente
    listen(sockfd, 5);
    addrlen = sizeof(serv_addr);
    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        max_sd = sockfd;
        for (int i = 0; i < max_clients ; i++)
        {
            printf("ok init readfds\n");
            sd = client_socket[i];
            if (sd > 0)
                FD_SET(sd, &readfds);
            if (sd > max_sd)
                max_sd = sd;
        }
        printf("max_sd: %d\n", max_sd);
        activity = select(max_sd + 1 , &readfds, NULL, NULL, NULL);
        if ((activity < 0) && (errno!=EINTR))
            perror("select");
            //printf("select error\n");
        if (FD_ISSET(sockfd, &readfds))
        {
            if ((newSockfd = accept(sockfd, (struct sockaddr *) 
                &serv_addr, (socklen_t*)&addrlen)) < 0 )
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , newSockfd , 
            inet_ntoa(serv_addr.sin_addr) , ntohs(serv_addr.sin_port));
            if( send(newSockfd, ":c1r4s2 001 jschreye :Welcome to the IRC Network, jschreye", 80, 0) != 80)
                perror("send");
            for (int i = 0; i < max_clients; i++)
            {
                if (client_socket[i] == 0)
                {
                    client_socket[i] = newSockfd;
                    std::cout << "socket added succefully :) \n" ;
                    break;
                }
            }
        }
        for (int i = 0; i < max_clients; i++)
        {
            sd = client_socket[i];
            if (FD_ISSET(sd, &readfds))
            {
                if ((n = read (sd, buffer, 255)) == 0)
                {
                    std::cout << "Host disconected ";
                    close(sd);
                    client_socket[i] = 0;
                }
                else
                {
                    buffer[n] = '\0';
                    printf("This is the message from %d: %s\n", sd, buffer);
                    //send(sd , "salut", strlen("salut"), 0);
                    send(sd , buffer, strlen(buffer) , 0);
                    //close(sd);  
                }
            }
        }
    }
    /*newSockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cliLen);
    bzero(buffer, 256);
    n = read(newSockfd, buffer, 255);
    if (n < 0)
        std::cerr << "ERROR reading from socket" << std::endl;
    std::cout << "Here is the message: " << buffer << std::endl;
    n = write(newSockfd, ":Welcome ", 18);
    if (n < 0)
        std::cerr << "ERROR writing to socket" << std::endl;
    close(sockfd);
    close(newSockfd);*/
    return (0);
}