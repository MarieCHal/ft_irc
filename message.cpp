/** @brief analyse le message
 * private ou pas?
 * si oui pour qui? est ce que c'est un user valide?
 * 
 * si c'est valid message appel write.cpp
 * pour ecrire soit a un client soit sur un channel
 * */
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

//revoie dans le output de tout les client du canal le input du client expediteur
void    message (t_data *data, int i, std::string cmd, std::string key_word) {

    if (data->client[i].chanel.length() == 0)
    {
        //std::cout << "key_word in message = " << key_word << std::endl;
        //std::cout << "nickname in message = " << data->client[i].nickname << std::endl;
        std::string msg = "421: ";
        msg += data->client[i].nickname;
        msg += " ";
        msg += key_word;
        msg += " :Unknown command";
        create_output(data, msg);
        send_one_user(data, i);
        return;
    }
    // si output
    //parse msg
        //si private_msg -> send_private_user(data, i);
        //sinon void send_msg()
    create_output(data, cmd);
    send_all_user(data, i);
}
/*
    std::string msg = " coucou \r\n";
*/