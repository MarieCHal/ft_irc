#include "data.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

void    quit(t_data *data, int i, std::string cmd)
{
    std::string reason;
    reason = "QUIT: ";
    if (cmd.length() < 5)
    {
        reason += data->client[i].nickname;
        create_output(data, reason);
    }
    else
    {
        size_t pos = cmd.find_first_of(' ', 0);
        cmd.erase(0, pos + 1);
        reason += cmd;
        create_output(data, reason); 
    }
    //clear client
    close(data->client[i].sd);

    //find the corresponding iterator to erase
    std::vector<client>::iterator it;
    it = data->client.begin();
    for (int j = 0; j != i ; j++)
        it++;
    data->client.erase(it);
    data->max_client--;
}