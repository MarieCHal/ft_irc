#include "data.hpp"

int cmd_user(t_data *data, int i, std::string cmd)
{
    size_t pos = cmd.find_first_of(':', 0);
    cmd.erase(0, pos + 1);
    int k = 0;
    for (size_t j = 0; j < cmd.length(); j++)
    {
        if (cmd[j] == ' ')
            k++;
    }
    if (k == 0)
        return (1);
    data->client[i].username = cmd;
    return (0);
}