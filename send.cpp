#include "data.hpp"
#include <sys/types.h>
#include <sys/socket.h>

void send_msg(t_data *data, int i)
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