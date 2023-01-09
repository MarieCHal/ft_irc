#include "data.hpp"

void check_cmd(t_data *data, int i, std::string key_word, std::string cmd)
{
    std::string possible_cmd [] = {"NICK", "USER", "JOIN", "PRIVMSG", "LIST", "QUIT", "KICK", "CAP", "ISON", "PING", "PASS", "NOTICE"};
    funtab function[] = {&nick, &user, &join, &privmsg, &list, &quit, &kick, &cap, &ison, &ping, &pass, &notice};
    size_t j = 0;
    while (j < 12)
    {
        if (key_word.compare(possible_cmd[j]) == 0)
        {
            ((*function[j])(data, i, cmd));
            return;
        }
        j++;
    }
    message_compose(5, data, data->server_name.c_str(), " 421 * ", key_word.c_str(), " :Unknown command");
    send_one_user(data, i);
    return;
}

