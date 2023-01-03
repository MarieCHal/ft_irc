/** @brief class user permet de stocker les info de chaque user
 * 
 * attributs:
 * - nickname
 * - username
 * - password
 * - operator (bool)
 * - pointeur sur vector channel
 * 
 * member function:
 * - getter/setter
 * 
 * */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <vector>

class client
{
    public:
    int sd; // client socketfd
    std::string nickname;
    std::string username;
    std::string password;
    bool        op;
    std::string chanel;
    
    client () {}
    client(int socketfd) : sd(socketfd) {}
    ~client() {}
};

#endif