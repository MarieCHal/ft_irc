#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "data.hpp"

int print_client(t_data *data)
{
    std::cout << "client socket descriptor: " << std::endl;
    for (size_t i = 0; i < data->client.size(); i++)
        std::cout << data->client[i].sd << std::endl;
    return (0);
}

/** TODO:
 * atoi
 *  */

int main(int ac, char **av)
{
    int portNo;//port serveur (2000)//
    int addrlen;
    int n;//retour read() write()
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
        return(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int reuseaddr_on = 1;
    if( setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR,
            &reuseaddr_on, sizeof( reuseaddr_on)) < 0)
        std::cout << "ERROR sockopt" << std::endl;
    ft_bzero((char *) &serv_addr, sizeof(serv_addr));
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
            std::cerr << "ERROR select" << std::endl;
        if (FD_ISSET(sockfd, &readfds))
        {
            if ((newSockfd = accept(sockfd, (struct sockaddr *) 
                &serv_addr, (socklen_t*)&addrlen)) < 0 )
            {
                std::cerr << "ERROR accept" << std::endl;
                return (1);
            }
            create_new_client(newSockfd, &data);
            //printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , newSockfd , 
            //inet_ntoa(serv_addr.sin_addr) , ntohs(serv_addr.sin_port));
            if( send(newSockfd, ":c1r4s2 001 jschreye :Welcome to the IRC Network, jschreye\r\n", 80, 0) != 80)
                std::cerr << "ERROR send" << std::endl;
        }
        for (int i = 0; i < data.max_client; i++)
        {
            sd = data.client[i].sd;
            if (FD_ISSET(sd, &readfds))
            {
                if ((n = read (sd, data.input, 255)) == 0)
                {
                    std::cout << "Host disconected ";
                    // envoyer a tous les clients que le client c'est deco ?
                    data.client.erase(data.client.begin() + i);
                    data.max_client--;
                    close(sd);
                }
                else
                {
                    //envoyer le message au parser a analyser
                    ft_bzero(data.output, strlen(data.output));
                    data.input[n] = '\0';
                    first_parsing(&data, i);
                    //printf("This is the message from %d: %s\n", sd, data.input);
                    //send(sd , data.output, strlen(data.output) , 0);
                    send_msg(&data, i);
                    ft_bzero(data.input, strlen(data.input));
                    //ft_bzero(data.output, strlen(data.output));
                }
            }
        }
    }
    return (0);
}