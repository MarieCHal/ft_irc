#include "data.hpp"

void list(t_data *data, int i, std::string cmd)
{
    std::string msg = data->client[i].nickname;
    (void)cmd;
    compose_reply(data, " 321 "," LIST ", " Channel :Users Name");
    send_one_user(data, i);
    for(int j = 0; j < data->max_client; j++)
    {
        if (data->client[i].chanel.empty())
            j++;
        if (j > 0 && data->client[j].chanel.compare(data->client[j - 1].chanel) == 0)
            j++;
        else
        {
            msg += " ";
            compose_reply(data, " 322 "," LIST ", data->client[j].chanel);
            send_one_user(data, i);
        }   
    }
    compose_reply(data, " 323 ", " LIST ", " :End of /LIST");
    send_one_user(data, i);
}
