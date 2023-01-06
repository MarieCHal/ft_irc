#include "data.hpp"

void    quit(t_data *data, int i, std::string cmd)
{
    std::string reason;
    std::vector<client>::iterator it;

    reason = "QUIT: ";
    if (cmd.length() < 5)
        compose_private_message(data, data->client[i].nickname, data->client[i].chanel, "");
    else
    {
        size_t pos = cmd.find_first_of(' ', 0);
        cmd.erase(0, pos + 1);
        compose_private_message(data, data->client[i].nickname, data->client[i].chanel, cmd);
    }
    send_all_user(data, i);
    close(data->client[i].sd);
    it = data->client.begin();
    for (int j = 0; j != i ; j++)
        it++;
    data->client.erase(it);
    data->max_client--;
}