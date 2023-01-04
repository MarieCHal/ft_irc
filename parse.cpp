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
//#include "exec.hpp"
#include <iostream>

/** if BUG:
 * penser au resultat de copy et au char * (dest)
 * */


int interpretor(t_data *data, int i, std::string cmd)
{
    size_t pos;
    std::string key_word;
    //std::cout << "cmd-length in interpretor = " << cmd.length() << std::endl;
    cmd.erase(cmd.length() - 2, cmd.length());
    cmd[cmd.length()] = '\0';
    //std::cout << "cmd in interpretor = " << cmd << std::endl;
    //std::cout << "cmd-length in interpretor = " << cmd.length() << std::endl;
    pos = cmd.find(' ');
    if (pos != std::string::npos)
        pos = cmd.find_first_of(32, 0);
    else
        pos = cmd.find_first_of('\0', 0);
    //std::cout << "pos in iterpretor = " << pos << std::endl;
    key_word.assign(cmd, 0, pos);
    //std::cout << "key_word in interpretor = " << key_word << std::endl;
    key_word = toUpper(key_word);
    check_cmd(data, i, key_word, cmd);//ATTENTION C'EST ICI QUE CA MERDE, A FAIRE LE 4 01 2023
    return (0);
}

//first parsing function (called in main)
int first_parsing(t_data *data, int i)
{
    size_t pos;
    std::string to_parse(data->input);
    std::string cmd;
    std::cout << "input = " << data->input << std::endl;
    while (to_parse.length() != 0)
    {
        pos = to_parse.find_first_of('\n', 0);
       //std::cout << "pos in first_parsing = " << pos << std::endl;
        cmd.assign(to_parse, 0, pos + 1);
        interpretor(data, i, cmd);
        to_parse.erase(0, pos + 1);
    }
    return (0);
}