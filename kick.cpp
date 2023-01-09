#include "data.hpp"

void kick(t_data *data, int i, std::string cmd)
{
    std::string chanel;
    std::string message;
    std::string user;
    
    if (data->client[i].op == false)
    {
        message_compose(5, data, data->server_name.c_str(), " 482 * ", data->client[i].nickname.c_str(), " :You are not Oper");
        send_one_user(data, i);
        return;
    }
    size_t pos = cmd.find_first_of(' ', 0);
    cmd.erase(0, pos + 1);
    pos = cmd.find_first_of(' ', 0);
    chanel.assign(cmd, 0, pos);
    if (chanel.compare(data->client[i].chanel) != 0)
    {
        message_compose(5, data, data->server_name.c_str(), " 442 * ", data->client[i].nickname.c_str(), " :You are not on that channel");
        send_one_user(data, i);
        return;
    }
    cmd.erase(0, pos + 1);
    pos = cmd.find_first_of(' ', 0);
    user.assign(cmd, 0, pos);
    cmd.erase(0, pos + 1);
    for (int j = 0; j < data->max_client; j++)
    {
        if (user.compare(data->client[j].nickname) == 0 && chanel.compare(data->client[j].chanel) == 0)
        {
            data->client[j].chanel.clear();
            message_compose(6, data, data->client[j].nickname.c_str(), " PRIVMSG ", "KICK", " :", cmd.c_str());
            send_one_user(data, j);
            message_compose(6, data, data->client[i].nickname.c_str(), " PRIVMSG ", ":Because", " :", cmd.c_str());
            send_all_user(data, i);
            return ;
        }
    }
    message_compose(5, data, data->server_name.c_str(), " 411 * ", user.c_str(), " :Not on channel");
    send_one_user(data, i);
}