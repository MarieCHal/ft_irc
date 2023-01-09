#include "data.hpp"

void ping(t_data *data, int i, std::string cmd)
{
    (void)cmd;
    compose_message(data, " PING ", data->client[i].nickname, "");
    send_one_user(data, i);
}