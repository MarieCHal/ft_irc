#include "data.hpp"

void nick(t_data *data, int i, std::string cmd)
{
    size_t pos = cmd.find_first_of(' ', 0); 
    int j = 0;

    cmd.erase(0, pos + 1);
    while (j < data->max_client)
    {
        if (cmd.compare(data->client[j].nickname) == 0)
        {
            message_compose(5, data, data->server_name.c_str(), " 433 * ", data->client[j].nickname.c_str(), " :already exist");
            send_one_user(data, i);
            return;
        }
        j++;
    }
    if (cmd.size() > 9)
    {
        message_compose(5, data, data->server_name.c_str(), " 433 * ", data->client[j].nickname.c_str(), " :nick name too long");
        send_one_user(data, i);
        return;
    }
    message_compose(5, data, " NICK ", data->client[i].nickname.c_str(), " ", cmd.c_str());
    send_one_user(data, i);
    data->client[i].nickname = cmd;
}