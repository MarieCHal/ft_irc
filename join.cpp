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
    size_t pos = cmd.find_first_of(32, 0);

    cmd.erase(0, pos + 1);
    if (cmd.find(' ') != std::string::npos)
    {
        compose_reply(data, " 403 ", data->client[i].chanel, ": Invalid caracter");
        send_one_user(data, i);
        return;
    }
    if (cmd.find(',') != std::string::npos)
    {
        compose_reply(data, " 403 ", data->client[i].chanel, ": Invalid caracter");
        send_one_user(data, i);
        return;
    }
    if (cmd.find(7) != std::string::npos)
    {
        compose_reply(data, " 403 ", data->client[i].chanel, ": Invalid caracter");
        send_one_user(data, i);
        return;
    }
    data->client[i].chanel = cmd;
    compose_message(data, " JOIN ", data->client[i].nickname, data->client[i].chanel);
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
    compose_reply(data, " 331 ", data->client[i].chanel, ": No topic is set");
    send_one_user(data, i);
}