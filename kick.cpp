#include "data.hpp"

void kick(t_data *data, int i, std::string cmd)
{
    std::string chanel;
    std::string message;
    std::string user;
    
    if (data->client[i].op == false)
    {
        compose_reply(data, " 482 * ", data->client[i].nickname, " :You are not Oper");
        send_one_user(data, i);
        return;
    }
    size_t pos = cmd.find_first_of(' ', 0);
    cmd.erase(0, pos + 1);
    pos = cmd.find_first_of(' ', 0);
    chanel.assign(cmd, 0, pos);
    if (chanel.compare(data->client[i].chanel) != 0)
    {
        compose_reply(data, " 442 * ", data->client[i].nickname, " :You are not on that channel");
        send_one_user(data, i);
        return;
    }
    cmd.erase(0, pos + 1);
    pos = cmd.find_first_of(' ', 0);
    user.assign(cmd, 0, pos);
    cmd.erase(0, pos + 1);
    std::cout << "user = " << user << std::endl;
    std::cout << "cmd = " << cmd << std::endl;
    for (int j = 0; j < data->max_client; j++)
    {
        if (user.compare(data->client[j].nickname) == 0 && chanel.compare(data->client[j].chanel) == 0)
        {
            data->client[j].chanel.clear();
            compose_private_message(data, data->client[j].nickname, "KICK", cmd);
            send_one_user(data, j);
            compose_private_message(data, data->client[i].nickname, ":Because", cmd);
            send_all_user(data, i);
            return ;
        }
    }
    compose_reply(data, " 411 * ", user, " :Not on channel");
    send_one_user(data, i);
}