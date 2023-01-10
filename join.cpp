#include "data.hpp"

// a voir pourquoi on ne voit plus quand on ce connect au channel
void join(t_data *data, int i, std::string cmd)
{
    size_t pos = cmd.find_first_of(32, 0);

    cmd.erase(0, pos + 1);
    if (cmd.find(' ') != std::string::npos)
    {
        message_compose(5, data, data->server_name.c_str(), " 403 ", data->client[i].chanel.c_str(), ": Invalid caracter");
        send_one_user(data, i);
        return;
    }
    if (cmd.find(',') != std::string::npos)
    {
        message_compose(5, data, data->server_name.c_str(), " 403 ", data->client[i].chanel.c_str(), ": Invalid caracter");
        send_one_user(data, i);
        return;
    }
    if (cmd.find(7) != std::string::npos)
    {
        message_compose(5, data, data->server_name.c_str(), " 403 ", data->client[i].chanel.c_str(), ": Invalid caracter");
        send_one_user(data, i);
        return;
    }
    data->client[i].chanel = cmd;
    message_compose(4, data, data->client[i].nickname.c_str(), " JOIN ", data->client[i].chanel.c_str());
    std::cout << "join -=" << data->output << std::endl;
    send_all_user(data, i);
    for (int j = 0; j < data->max_client; j++)
    {
        if (cmd.compare(data->client[j].chanel) == 0 && j != i)
        {
            data->client[i].op = false;
            return ;
        }
    }
    data->client[i].op = true;
    message_compose(5, data, data->server_name.c_str(), " 331 ", data->client[i].chanel.c_str(), ": No topic is set");
    send_one_user(data, i);
}