#include "data.hpp"

void ison(t_data *data, int i, std::string cmd)
{
    size_t pos = cmd.find_first_of(' ', 0);

    cmd.erase(0, pos + 1);
    message_compose(5, data, data->server_name.c_str(), " 303 ", data->client[i].nickname.c_str(), cmd.c_str());
    send_one_user(data, i);
}