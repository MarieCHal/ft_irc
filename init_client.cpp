#include "data.hpp"

int create_new_client(int socketfd, t_data *data, sockaddr_in serv_addr)
{
    client newClient(socketfd);
    char client_hostname[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &serv_addr.sin_addr, client_hostname, INET_ADDRSTRLEN) == NULL)
    {
        std::cerr << "Error: inet_ntop() failed." << std::endl;
        return -1;
    }
    newClient.client_ip = client_hostname;
    data->client.push_back(newClient);
    data->max_client++;
    if (data->pwd_server.length() != 0)
    {
        message_compose(4, data, data->server_name.c_str(), " 464 ", ":Please enter the password");
        send(socketfd, data->output, ft_strlen(data->output), 0);
    }
    return (0);
}
