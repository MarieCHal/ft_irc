/** @brief sorte de base de donnee
 * fait le lien entre le main (la recuperation des donnees)
 * et le code d'analyise et d'execution a faire afin de 
 * renvoyer une reponse ou d'executer la demmande du client
 * 
 * attributs:
 * - tableu de client
 * - tableau de pointeur sur objet channel (vectoro f vector)
 *      -> pos [0] = password
 *      -> commence a pos 1 pour stocker les sockets
 * - 
 * 
 * attributs:
 * - input message
 * - outpus message (peutetre pas ici)
 * */

#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <map>
#include <vector>
#include "client.hpp"


typedef struct s_data
{
    std::vector<client> client; // le tableau des clients
    std::map<std::string, std::vector<int> > chanels; // les objets 
    int     max_client;

    char input[512];
    char output[512];

}       t_data;

/*void    cmd(std::string cmd)
typedef void()*/

int create_new_client(int socketfd, t_data *data);
int first_parsing(t_data *data, int i);
#endif