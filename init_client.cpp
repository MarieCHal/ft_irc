

#include "client.hpp"
#include "data.hpp"

/** @brief creates a new user
 * 
 * */



int create_new_client(int socketfd, t_data *data)
{
    // creer un nouveau client
    //client *newClient = new client(socketfd);
    // create dynamiquement 
    client newClient(socketfd);
    // ajoute un client au vector de dlient de data
    data->client.push_back(newClient);
    data->max_client++;
    return (0);
}
