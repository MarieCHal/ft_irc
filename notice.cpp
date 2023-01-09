#include "data.hpp"

void notice(t_data *data, int i, std::string cmd)
{
    std::string user;
    std::string chan;
    size_t pos = cmd.find_first_of(' ', 0);

    cmd.erase(0, pos + 1);
    pos = cmd.find_first_of(' ', 0);
    if (cmd[0] == '#')
    {
        chan.assign(cmd, 0, pos);
        cmd.erase(0, pos + 2);// ou + 1
        compose_private_message(data, data->client[i].nickname, data->client[i].chanel, cmd);
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
                    compose_private_message(data, data->client[i].nickname, " PRIVMSG ", cmd);
                    send_one_user(data, j);
                    return ;
                }
            }
        }
    }
}