#include "data.hpp"

void user(t_data *data, int i, std::string cmd)
{
    size_t pos = cmd.find_first_of(':', 0);
    cmd.erase(0, pos + 1);
    std::cout << "cmd de user = " << cmd << std::endl;
    int k = 0;
    for (size_t j = 0; j < cmd.length(); j++)
    {
        if (cmd[j] == ' ')
            k++;
    }
    if (k == 0)
    {
        create_output(data, "USER: invalid argument\r\n");
        return;
    }
    data->client[i].username = cmd;
    create_output(data, "USER: OK\r\n");
}