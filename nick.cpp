#include "data.hpp"
// 9 caratere maximum
int cmd_nick(t_data *data, int i, std::string cmd)
{
    int k = 0;
    for (size_t j = 0; j < cmd.length(); j++)
    {
        if (cmd[j] == ' ')
            k++;
    }
    if (k != 1)
        return (1);
    size_t pos = cmd.find_first_of(' ', 0);
    cmd.erase(0, pos + 1);
    if (cmd.find(' '))
        return;
    int j = 0;
    while (j < data->max_client)
    {
        if (cmd.compare(data->client[j].nickname) == 0)
            return (1);
        j++;
    }
    if (cmd.size() > 9)
        return (1);
    data->client[i].nickname = cmd;
    return (0);
}