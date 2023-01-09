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

int create_new_client(int socketfd, t_data *data, sockaddr_in serv_addr)
{
    // creer un nouveau client
    //client *newClient = new client(socketfd);
    // create dynamiquement 
    client newClient(socketfd);
    // ajoute un client au vector de dlient de data
    char client_hostname[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &serv_addr.sin_addr, client_hostname, INET_ADDRSTRLEN) == NULL)
    {
        std::cerr << "Error: inet_ntop() failed." << std::endl;
        return -1;
    }
    newClient.client_ip = client_hostname;
    std::cout << "newClient.client_ip = " << newClient.client_ip << std::endl;
    data->client.push_back(newClient);
    data->max_client++;
    if (data->pwd_server.length() != 0)
    {
        message_compose(4, data, data->server_name.c_str(), " 464 ", ":Please enter the password");
        send(socketfd, data->output, ft_strlen(data->output), 0);
    }
    return (0);
}
