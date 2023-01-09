#include "data.hpp"

void user(t_data *data, int i, std::string cmd)
{  
    int k = 0;
    size_t pos = cmd.find_first_of(':', 0);
    
    cmd.erase(0, pos + 1);
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
    message_compose(5, data, data->server_name.c_str(), " 001 ",
                    data->client[i].nickname.c_str(), ": Welcome to the IRC Network");
    send_one_user(data, i);
}
