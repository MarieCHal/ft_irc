#include "data.hpp"

void privmsg(t_data *data, int i, std::string cmd)
{
    std::string user;
    std::string chan;
    size_t pos = cmd.find_first_of(' ', 0);

    cmd.erase(0, pos + 1);
    pos = cmd.find_first_of(' ', 0);
    if (cmd[0] == '#')
    {
        chan.assign(cmd, 0, pos);
        cmd.erase(0, pos + 2);
        message_compose(6, data, data->client[i].nickname.c_str(), " PRIVMSG ", data->client[i].chanel.c_str(), " :", cmd.c_str());
        send_all_user(data, i);
        return ;
    }
    else
    {
        user.assign(cmd, 0, pos);
        cmd.erase(0, pos + 1);
        for (int j = 0; j < data->max_client; j++)
        {
            if (user.compare(data->client[j].nickname) == 0)
            {
                if (data->client[j].chanel.compare(data->client[i].chanel) == 0)
                {
                    message_compose(6, data, data->client[i].nickname.c_str(), " PRIVMSG ",  " PRIVMSG ", " :", cmd.c_str());
                    send_one_user(data, j);
                    return ;
                }
            }
        }
        message_compose(5, data, data->server_name.c_str(), " 411 * ", user.c_str(), " :No recipient given");
        send_one_user(data, i);
    }
}
