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
    data->client[i].chanel = cmd;
    msg += "PRIVMSG ";
    msg += data->client[i].chanel;
    msg += " :";
    msg += "42 ";
    create_output(data, msg);
    send_all_user(data, i);
    for (int j = 0; j < data->max_client; j++)
    {
        if (cmd.compare(data->client[j].chanel) == 0 && j != i)
        {
            data->client[i].op = false;
            return ;
        }
    }
    data->client[i].op = true;
    //std::cout << data->client[i].nickname << " est-il op? " << data->client[i].op << std::endl;
}