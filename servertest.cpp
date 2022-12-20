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

#include "data.hpp"

int print_client(t_data *data)
{
    std::cout << "client socket descriptor: " << std::endl;
    for (size_t i = 0; i < data->client.size(); i++)
        std::cout << data->client[i].sd << std::endl;
    return (0);
}

int main(int ac, char **av)
{
    int portNo;//port serveur (2000)//
    int addrlen;
    int n;//retour read() write()
    //char buffer[256];//pour lire le message depuis la socket
    struct sockaddr_in serv_addr;//est une structure contenant une adresse internet. Cette structure est définie dans netinet/in.h.

    t_data data;
    data.max_client = 0;
    fd_set readfds;
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
    /*for (int i = 0 ; i < data.max_client ; i++)
        data.client[i].sd = 0;*/

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
        perror("ERROR on binding");
    //ecoute la socket du serveur et definie le nb de connection en attente
    listen(sockfd, 5);
    addrlen = sizeof(serv_addr);
    while (1)
    {
        print_client(&data);
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        max_sd = sockfd;
        for (int i = 0; i < data.max_client ; i++)
        {
            sd = data.client[i].sd;
            if (sd > 0)
                FD_SET(sd, &readfds);
            if (sd > max_sd)
                max_sd = sd;
        }
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
            create_new_client(newSockfd, &data);
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , newSockfd , 
            inet_ntoa(serv_addr.sin_addr) , ntohs(serv_addr.sin_port));
            if( send(newSockfd, ":c1r4s2 001 jschreye :Welcome to the IRC Network, jschreye\r\n", 80, 0) != 80)
                perror("send");
            /*for (int i = 0; i < data.max_client; i++)
            {
                if (data.client[i].sd == 0)
                {
                    client_socket[i] = newSockfd;
                    std::cout << "socket added succefully :) \n" ;
                    break;
                }
            }*/
        }
        for (int i = 0; i < data.max_client; i++)
        {
            sd = data.client[i].sd;
            if (FD_ISSET(sd, &readfds))
            {
                if ((n = read (sd, data.input, 255)) == 0)
                {
                    std::cout << "Host disconected ";
                    //data.client[i].sd = 0;
                    // clear et effacer le client
                    data.client.erase(data.client.begin() + i);
                    data.max_client--;
                    close(sd);
                }
                else
                {
                    //envoyer le message au parser a analyser
                    data.input[n] = '\0';
                    first_parsing(&data, i);
                    printf("This is the message from %d: %s\n", sd, data.input);
                    send(sd , data.input, strlen(data.input) , 0);
                }
            }
        }
    }
    return (0);
}