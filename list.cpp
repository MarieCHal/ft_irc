#include "data.hpp"

void list(t_data *data, int i, std::string cmd)
{
    std::string reponse;
    (void)cmd;

    for(int j = 0; j < data->max_client; j++)
    {
        if (data->client[i].chanel.empty())
            j++;
        if (j > 0 && data->client[j].chanel.compare(data->client[j - 1].chanel) == 0)
            j++;
        else
        {
            reponse += ":c1r4s2 322 ";
            reponse += data->client[i].nickname;
            reponse += ' ';
            reponse += data->client[j].chanel;
            reponse += "\n";
        }   
    }
    reponse += ":End of /LIST";
    create_output(data, reponse);
    send_one_user(data, i);
}