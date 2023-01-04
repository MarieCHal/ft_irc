#include "client.hpp"
#include "data.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

/** @brief creates a new user
 * 
 * */

/*
void get_client_ip(client newClient)
{
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);
    int result = getpeername(newClient.sd, (sockaddr*)&clientAddress, &clientAddressLen);
    if (result == 0)
    {
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddress.sin_addr, clientIP, INET_ADDRSTRLEN);
        newClient.client_ip(clientIP);
    }
}
*/
int create_new_client(int socketfd, t_data *data)
{
    // creer un nouveau client
    //client *newClient = new client(socketfd);
    // create dynamiquement 
    client newClient(socketfd);
    // ajoute un client au vector de dlient de data
    data->client.push_back(newClient);
    data->max_client++;
    //get_client_ip(newClient);
    return (0);
}
