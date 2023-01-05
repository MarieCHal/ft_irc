#include "data.hpp"

void kick(t_data *data, int i, std::string cmd)
{
    std::string user;
    std::string chanel;
    std::string message;

    if (data->client[i].op == false)
    {
        create_output(data, "you can't execute this command, you are not an operator");
        send_one_user(data, i);
    }
    else
    {
        size_t pos = cmd.find_first_of(' ', 0);
        cmd.erase(0, pos + 1);
        std::cout << "cmd in kick first erase: " << cmd << std::endl;
        pos = cmd.find_first_of(' ', 0);
        user.assign(cmd, 0, pos);
        std::cout << "user in kick: " << user << std::endl;
        cmd.erase(0, pos + 1);
        pos = cmd.find_first_of(' ', 0);
        if (pos != std::string::npos)
        {
            chanel.assign(cmd, 0, pos);
            cmd.erase(0, pos + 1);
            message = cmd;
            std::cout << "message: " << message << std::endl; 
        }
        else
            chanel = cmd;
        std::cout << "chanel in kick: " << chanel << std::endl;
        for (int j = 0; j < data->max_client; j++)
        {
            if (user.compare(data->client[j].nickname) == 0 && chanel.compare(data->client[j].chanel) == 0)
            {
                std::string msg = data->client[i].nickname;
                msg += " banned you from channel: ";
                msg += chanel;
                if (!message.empty())
                {
                    msg += " :";
                    msg += message;   
                }
                create_output(data, msg);
                send_one_user(data, j);
                data->client[j].chanel.clear();
                return ;
            }
        }
        create_output(data, "Invalid user or channel");
        send_one_user(data, i);
    }
}