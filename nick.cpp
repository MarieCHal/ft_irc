#include "data.hpp"
// 9 caratere maximum
void nick(t_data *data, int i, std::string cmd)
{
    size_t pos = cmd.find_first_of(' ', 0); 
    int j = 0;

    cmd.erase(0, pos + 1);
    while (j < data->max_client)
    {
        if (cmd.compare(data->client[j].nickname) == 0)
        {
            compose_reply(data, " 433 * ", data->client[j].nickname, " :already exist");
            send_one_user(data, i);
            return;
        }
        j++;
    }
    if (cmd.size() > 9)
    {
        create_output(data, "NICK: nickName too long");
        send_one_user(data, i);
        return;
    }
    compose_message(data, " NICK ", data->client[i].nickname, cmd);
    send_one_user(data, i);
    data->client[i].nickname = cmd;
}