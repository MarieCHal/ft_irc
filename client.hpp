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
        client(int socketfd) : sd(socketfd)
        {
            op = false;
            pass = false;
            pos = 0; 
        }
        client(const client &rhs) {*this = rhs;}
        client &operator= (const client &rhs)
        {
            if (&rhs != this)
            {
                nickname = rhs.nickname;
                username = rhs.username;
                password = rhs.password;
                client_ip = rhs.client_ip;
                cmd = rhs.cmd;
                chanel = rhs.chanel;
                op = rhs.op;
                pass = rhs.pass;
                sd = rhs.sd;
                pos = rhs.pos;   
            }
            return *this;
        }
        ~client() {}
};

#endif