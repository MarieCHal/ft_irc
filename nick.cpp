#include "data.hpp"
// 9 caratere maximum
void nick(t_data *data, int i, std::string cmd)
{
    int k = 0;
    for (size_t j = 0; j < cmd.length(); j++)
    {
        if (cmd[j] == ' ')
            k++;
    }
    if (k != 1)
    {
        create_output(data, "NICK: invalid input\r\n");
        return;
    }
    size_t pos = cmd.find_first_of(' ', 0);
    cmd.erase(0, pos + 1);
    std::cout << "cmd de nick = " << cmd << std::endl;
    int j = 0;
    while (j < data->max_client)
    {
        if (cmd.compare(data->client[j].nickname) == 0)
        {
            create_output(data, "NICK: already exist\r\n");
            return;
        }
        j++;
    }
    if (cmd.size() > 9)
    {
        create_output(data, "NICK: nickName too long\r\n");
        return;
    }
    data->client[i].nickname = cmd;
    std::cout << data->client[i].nickname << std::endl;
}