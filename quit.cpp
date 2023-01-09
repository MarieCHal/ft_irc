#include "data.hpp"

void    quit(t_data *data, int i, std::string cmd)
{
    std::string reason;
    std::vector<client>::iterator it;

    reason = "QUIT: ";
    if (cmd.length() < 5)
        message_compose(6, data, data->client[i].nickname.c_str(), " PRIVMSG ", data->client[i].chanel.c_str(), " :", "");
    else
    {
        size_t pos = cmd.find_first_of(' ', 0);
        cmd.erase(0, pos + 1);
        message_compose(6, data, data->client[i].nickname.c_str(), " PRIVMSG ", data->client[i].chanel.c_str(), " :", cmd.c_str());
    }
    send_all_user(data, i);
    close(data->client[i].sd);
    it = data->client.begin();
    for (int j = 0; j != i ; j++)
        it++;
    data->client.erase(it);
    data->max_client--;
}