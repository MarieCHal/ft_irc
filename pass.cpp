#include "data.hpp"

void pass(t_data *data, int i, std::string cmd)
{
    size_t pos = cmd.find_first_of(' ', 0);
    size_t pospass = cmd.find("PASS", 0);

    if (pospass != std::string::npos)
    {
        cmd.erase(0, pos + 1);
        if (cmd.compare(data->pwd_server) == 0)
            data->client[i].pass = 1;
        else 
        {
            message_compose(4, data, data->server_name.c_str(), " 464 ", ":Please enter the password");
            send_one_user(data, i);
        }
    }
    else
        return ;
}