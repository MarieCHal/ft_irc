#include "data.hpp"

void privmsg(t_data *data, int i, std::string cmd)
{
    std::string user;

    size_t pos = cmd.find_first_of(' ', 0);
    cmd.erase(0, pos + 1);
    pos = cmd.find_first_of(' ', 0);
    user.assign(cmd, 0, pos);
    cmd.erase(0, pos + 1);
    for (int j = 0; j < data->max_client; j++)
    {
        if (user.compare(data->client[j].nickname) == 0)
        {
            std::string msg = data->client[i].nickname;
            msg += ": ";
            msg += cmd;
            create_output(data, msg);
            send_one_user(data, j);
            return ;
        }
    }
    create_output(data, "Invalid user");
    send_one_user(data, i);
}