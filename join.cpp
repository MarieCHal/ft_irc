/** @brief parse la commande join
 * 
 * appelé par parse.cpp si c'est detecté
 * 
 * si la commande est valide:
 * appel la exec/join.cpp pour executer la commande
 * et envoie tous les arguments necessaires
 * 
 * */

#include "data.hpp"

void join(t_data *data, int i, std::string cmd)
{
    std::string msg;
    size_t pos = cmd.find_first_of(32, 0);
    cmd.erase(0, pos + 1);
    //if there is any of those characters the channel name is invalid
    std::cout << "cmd in join = " << cmd << std::endl;
    if (cmd.find(' ') && cmd.find(',') && cmd.find(7) && cmd[0] != '#')
    {
        create_output(data, "Invalid Channel name.");
        send_one_user(data, i);
        return;
    }
    else
    {
        data->client[i].chanel = cmd;
    }
    msg += data->client[i].nickname;
    msg += " joined this channel!";
    create_output(data, msg);
    send_all_user(data, i);
}