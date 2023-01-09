#include "data.hpp"

void ison(t_data *data, int i, std::string cmd)
{
    size_t pos = cmd.find_first_of(' ', 0);

    cmd.erase(0, pos + 1);
    compose_reply(data, " 303 ", data->client[i].nickname, cmd);
    send_one_user(data, i);
}