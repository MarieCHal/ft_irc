#include "data.hpp"

void    nick (t_data *data, int i, std::string cmd) {
    std::cout << "cmd: " << cmd << "\ni: " << i << "\nsocket descriptor: " << data->client[i].sd << std::endl;
    printf("\nNIIIIICK\n");
}
void    user (t_data *data, int i, std::string cmd) {
    std::cout << "cmd: " << cmd << "\ni: " << i << "\nsocket descriptor: " << data->client[i].sd << std::endl;
    printf("\nUUUUUUUUSER\n");
}
void    join (t_data *data, int i, std::string cmd) {
    std::cout << "cmd: " << cmd << "\ni: " << i << "\nsocket descriptor: " << data->client[i].sd << std::endl;
    printf("\nJOIIIIIIIIiN\n");
    parse_join(data, i, cmd);
}
void check_cmd(t_data *data, int i, std::string key_word, std::string cmd)
{
    std::string possible_cmd [] = {"NICK", "USER", "JOIN", "CAP"};
    funtab function[] = {&nick, &user, &join, &join};
    size_t j = 0;
    while (key_word.compare(possible_cmd[j]) != 0 && j < possible_cmd->length())
        j++;
    if (j < possible_cmd->length())
        ((*function[j])(data, i, cmd));
    //else appel une fonction qui parse le message
}