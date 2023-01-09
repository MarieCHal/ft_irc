#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <vector>

//inistialiser avec le constructeur les variables

class client
{
    public:

        std::string nickname;
        std::string username;
        std::string password;
        std::string client_ip;
        std::string cmd;
        std::string chanel;
        bool        op;
        bool        pass;
        char buffer[512];
        int         sd; // client socketfd
        int         pos;
    
        client () {}
        client(int socketfd) : sd(socketfd) {}
        ~client() {}
};

#endif