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


//void send_private_msg()



//revoie dans le output de tout les client du canal le input du client expediteur
void    message (t_data *data, int i, std::string cmd, std::string key_word) {
    (void)cmd;
    if (data->client[i].chanel.length() == 0)
    {
        std::string msg = "421: ";
        std::cout << "key_word in message = " << key_word << std::endl;
        msg += data->client[i].nickname;
        msg += " ";
        msg += key_word;
        msg += " :Unknown command\r\n";
        create_output(data, msg);
        return;
    }
    //parse msg
        //si private_msg -> void send_private_msg()
        //sinon void send_msg()
    create_output(data, "Your msg\r\n");

}
/*
    std::string msg = " coucou \r\n";
*/