/** @brief analyse le message
 * private ou pas?
 * si oui pour qui? est ce que c'est un user valide?
 * 
 * si c'est valid message appel write.cpp
 * pour ecrire soit a un client soit sur un channel
 * */
#include "../data.hpp"

void    message (t_data *data, int i, std::string cmd) {
    std::cout << "cmd: " << cmd << "\ni: " << i << "\nsocket descriptor: " << data->client[i].sd << std::endl;
    printf("\nJOIIIIIIIIiN\n");
}