#include "data.hpp"

void user(t_data *data, int i, std::string cmd)
{
    
    size_t pos = cmd.find_first_of(':', 0);
    cmd.erase(0, pos + 1);
    std::cout << "cmd de user = " << cmd << std::endl;
    int k = 0;
    for (size_t j = 0; j < cmd.length(); j++)
    {
        if (cmd[j] == ' ')
            k++;
    }
    if (k == 0)
    {
        create_output(data, "USER: invalid argument");
        send_one_user(data, i);
        return;
    }
    data->client[i].username = cmd;
    std::string msg = ":";
    msg += data->server_name;
    msg += " 001 ";
    msg += data->client[i].nickname;
    msg += ": Welcome to the IRC Network";
    create_output(data, msg);
    send_one_user(data, i);
}
