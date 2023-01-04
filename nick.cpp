#include "data.hpp"
// 9 caratere maximum
void nick(t_data *data, int i, std::string cmd)
{
    std::string msg;
    //std::cout << "cmd de nick = " << cmd << std::endl;
    int k = 0;
    for (size_t j = 0; j < cmd.length(); j++)
    {
        if (cmd[j] == ' ')
            k++;
    }
    if (k != 1)
    {
        create_output(data, "NICK: invalid input");
        send_one_user(data, i);
        return;
    }
    size_t pos = cmd.find_first_of(' ', 0);
    cmd.erase(0, pos + 1);
    //std::cout << "cmd de nick = " << cmd << std::endl;
    int j = 0;
    while (j < data->max_client)
    {
        if (cmd.compare(data->client[j].nickname) == 0)
        {
            create_output(data, "NICK: already exist");
            send_one_user(data, i);
            return;
        }
        j++;
    }
    if (cmd.size() > 9)
    {
        //std::cout << "cmd-length de nick = " << cmd.length() << std::endl;
        //std::cout << "coucou" << std::endl;
        create_output(data, "NICK: nickName too long");
        send_one_user(data, i);
        return;
    }
    data->client[i].nickname = cmd;
    msg = ":Your new nickname is ";
    msg += data->client[i].nickname;
    msg += '!';
    create_output(data, msg);
    send_one_user(data, i);
    std::cout << "coucou " << data->client[i].nickname << std::endl;
}