/** @brief parse la commande join
 * 
 * appelé par parse.cpp si c'est detecté
 * 
 * si la commande est valide:
 * appel la exec/join.cpp pour executer la commande
 * et envoie tous les arguments necessaires
 * 
 * check:
 * 1. cut the command
 * 2. check if it is valide number of arguments 
 * 3. check if the channel exists or not
 * 3. if it is the first time that it joined (creates or join )
 * 
 * if join successful RPL_NAMREPLY
 * */


#include "../data.hpp"

int parse_join(t_data *data, int i, std::string args)
{
    size_t pos = args.find_first_of(32, 0);
    args.erase(0, pos + 1);
    //if there is any of those characters the channel name is invalid
    if (args.find(' ') || args.find(',') || args.find(7) || args[0] != '#')
        std::cout << "Invalid Channel name: " << args << std::endl;
    else
    {
        data->client[i].chanel = args;
    }
    return (0);
}