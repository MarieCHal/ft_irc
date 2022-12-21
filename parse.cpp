/**  @brief analyse le buffere de read de data
 * check si c'est un message ou un une commande
 *
 * -> parser message 
 * -> parser commande (ex Join)
 *  
 * 
 * permier message: CAP LS 302 (renvoyer un message wellcome, connection succefull)
 * deuxieme message: 
 * 
 * 1. parwer en fonction de \n (tableau de ligne de commande)
 * 2. -> commande: parser en fonction des espace (1.commande, 2.,3., etc, arguments)
 *    -> message (parsing orgine(prefix), reste du message, pour qui)
 * 
 * commands:
 * - NICK
 * - USER
 * - JOIN (#chanelname)
 * - LIST (/join)
 * - QUIT
 * 
 * */

#include "data.hpp"
#include "exec.hpp"
#include <iostream>


int interpretor(t_data *data, int i, char * copy_cmd)
{
    size_t pos;
    std::string parsed = copy_cmd;
    pos = parsed.find_first_of(32, 0);
    char cmd[pos];
    parsed.copy(cmd, pos, 0);
    std::string newCmd = cmd;
    /*for(size_t i = 0; cmd[i]; i++)
    {
        newCmd[i] = toupper(cmd[i]);
    }*/
    std::cout << "new cmd: " << newCmd << std::endl;
    exec_input exec(parsed);
    exec.check_cmd(data, i, newCmd);
    return (0);
}

//first parsing function (called in main)
int first_parsing(t_data *data, int i)
{
    size_t pos;
    std::string to_parse = data->input;

    while (to_parse.length() != 0)
    {
        pos = to_parse.find_first_of('\n', 0);
        char copy_cmd[pos];
        to_parse.copy(copy_cmd, pos, 0);
        std::cout << "from client socket fd: " << data->client[i].sd << std::endl;
        
        //send copy_cmd to see if it is a command or message
        interpretor(data, i, copy_cmd);
        to_parse.erase(0, pos + 1);
        bzero(copy_cmd, pos);
    }
    return (0);
}