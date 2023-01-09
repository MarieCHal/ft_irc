#include "data.hpp"

void list(t_data *data, int i, std::string cmd)
{
   // std::string msg = data->client[i].nickname;
    (void)cmd;
    message_compose(5, data, data->server_name.c_str(), " 321 "," LIST ", " Channel :Users Name");
    send_one_user(data, i);
    for(int j = 0; j < data->max_client; j++)
    {
        if (data->client[i].chanel.empty())
            j++;
        if (j > 0 && data->client[j].chanel.compare(data->client[j - 1].chanel) == 0)
            j++;
        else
        {
            //msg += " ";
            message_compose(5, data, data->server_name.c_str(), " 322 "," LIST ", data->client[j].chanel.c_str());
            send_one_user(data, i);
        }   
    }
    message_compose(5, data, data->server_name.c_str(), " 323 ", " LIST ", " :End of /LIST");
    send_one_user(data, i);
}
