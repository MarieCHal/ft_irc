#include "data.hpp"
// 9 caratere maximum
void nick(t_data *data, int i, std::string cmd)
{
    std::string msg = ":";
    //std::cout << "cmd de nick = " << cmd << std::endl;
    int k = 0;
    for (size_t j = 0; j < cmd.length(); j++)
    {
        if (cmd[j] == ' ')
            k++;
    }
    /*
    if (k != 1)
    {
        msg += data->server_name;
        msg += " 431 * ";
        msg += data->client[i].nickname;
        msg += " :no nickname given";
        create_output(data, msg);
        send_one_user(data, i);
        return;
    }
    */
    size_t pos = cmd.find_first_of(' ', 0);
    cmd.erase(0, pos + 1);
    //std::cout << "cmd de nick = " << cmd << std::endl;
    int j = 0;
    while (j < data->max_client)
    {
        if (cmd.compare(data->client[j].nickname) == 0)
        {
            msg += data->server_name;
            msg += " 433 * ";
            msg += data->client[i].nickname;
            msg += " :already exist";
            create_output(data, msg);
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
    msg += data->client[i].client_ip;
    //msg += "!";
    //msg += data->server_name;
    //msg += " ";
    msg += " NICK ";
    msg += cmd;
    data->client[i].nickname = cmd;
    create_output(data, msg);
    send_one_user(data, i);
    std::cout << "coucou " << data->client[i].nickname << std::endl;
}