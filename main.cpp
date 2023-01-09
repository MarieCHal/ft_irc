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
 * atoi fait
 * strlen fait
 *  */

int main(int ac, char **av)
{
    struct sockaddr_in serv_addr;//est une structure contenant une adresse internet. Cette structure est définie dans netinet/in.h.
    t_data data;
    fd_set readfds;
    int portNo;//port serveur (2000)//
    int addrlen;
    int n;//retour read() write()
    int sockfd;//retour socket() server
    int newSockfd;//retour socket() client
    int max_sd;
    int sd;
    int activity;
    
    
    data.max_client = 0;
    get_host_name(&data);
    //ft_bzero(data.input, ft_strlen(data.input));
    ft_bzero(data.output, ft_strlen(data.output));
    //clear/init fdset
    FD_ZERO(&readfds);
    if(ac < 2 || ac > 3)
    {
        std::cerr << "ERR0R, invalid argument" << std::endl;
        return(1);
    }
    portNo = ft_atoi(av[1]);
    if (portNo != 6667)
    {
        std::cerr << "ERR0R, invalid port, please use port 6667" << std::endl;
        return(1);
    }
    if(ac == 3)
    {
        data.pwd_server = av[2];
        std::cout << data.pwd_server << std::endl;
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int reuseaddr_on = 1;
    if( setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR,
            &reuseaddr_on, sizeof( reuseaddr_on)) < 0)
        std::cout << "ERROR sockopt" << std::endl;
    ft_bzero((char *) &serv_addr, sizeof(serv_addr));

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
            create_new_client(newSockfd, &data, serv_addr);
        }
        for (int i = 0; i < data.max_client; i++)
        {
            sd = data.client[i].sd;
            if (FD_ISSET(sd, &readfds))
            {
                if ((n = read (sd, data.client[i].buffer, 255)) == 0)
                //if ((n = read (sd, data.input, 255)) == 0)
                {
                    std::cout << "Host disconected " << std::endl;
                    // envoyer a tous les clients que le client c'est deco ?
                    data.client.erase(data.client.begin() + i);
                    data.max_client--;
                    close(sd);
                }
                else
                {
                    //envoyer le message au parser a analyser
                    //n = read (sd, data.input, 255);
                    ft_bzero(data.output, ft_strlen(data.output));
                    data.client[i].buffer[n] ='\0';
                    //std::cout << "buffer: " << data.client[i].buffer << std::endl;
                    //data.input[n] = '\0';
                    if (buffer_check(&data, i) == 0)
                        first_parsing(&data, i);
                    //printf("This is the message from %d: %s\n", sd, data.input);
                    //send(sd , data.output, strlen(data.output) , 0);
                    //send_all_user(&data, i);
                }
            }
        }
    }
    return (0);
}