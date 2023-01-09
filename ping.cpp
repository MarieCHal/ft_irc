#include "data.hpp"

void ping(t_data *data, int i, std::string cmd)
{
    (void)cmd;
    message_compose(4, data, " PING ", data->client[i].nickname.c_str(), "");
    send_one_user(data, i);
}