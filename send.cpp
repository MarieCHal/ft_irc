#include "data.hpp"
#include <sys/types.h>
#include <sys/socket.h>

void send_all_user(t_data *data, int i)
{
    int k = 0;

    while (k < data->max_client)
    {
        if (data->client[k].chanel.compare(data->client[i].chanel) == 0)
        {
            send(data->client[k].sd, data->output, strlen(data->output), 0);
        }
        k++;
    } 
}

void send_one_user(t_data *data, int i)
{
    send(data->client[i].sd, data->output, strlen(data->output), 0);
}
