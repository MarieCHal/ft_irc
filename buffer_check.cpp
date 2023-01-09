#include "data.hpp"
#include "stdlib.h"
#include <string>

int buffer_check(t_data *data, int i)
{
    size_t len;
    size_t pos;
    std::string last_cmd;
    std::string tmp;
    
    len = strlen(data->client[i].buffer);
    tmp = data->client[i].buffer;
    data->client[i].cmd += tmp;
    pos = data->client[i].cmd.find_last_of("\r\n", data->client[i].cmd.length() -3);
    if ( pos != std::string::npos)
        last_cmd.assign(data->client[i].cmd, pos, data->client[i].cmd.length());
    else
        last_cmd.assign(data->client[i].cmd, 0);
    last_cmd.erase(last_cmd.length() -2, last_cmd.length());
    pass(data, i, last_cmd);
    if (data->pwd_server.length() != 0 && data->client[i].pass == false)
        return 1;
    if (data->client[i].buffer[len - 1] == '\n')
    {
        data->input = data->client[i].cmd;
        data->client[i].cmd.clear();
        ft_bzero(data->client[i].buffer, ft_strlen(data->client[i].buffer));
        return 0;
    }
    return 1;
}