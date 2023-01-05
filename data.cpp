#include "data.hpp"

void check_cmd(t_data *data, int i, std::string key_word, std::string cmd)
{

    //std::cout << "key_word de check_cmd = " << key_word << std::endl;
    std::string possible_cmd [] = {"NICK", "USER", "JOIN", "PRIVMSG", "LIST", "QUIT", "KICK", "CAP"};
    funtab function[] = {&nick, &user, &join, &privmsg, &list, &quit, &kick, &cap};
    size_t j = 0;
    //std::cout << "cmd de check_cmd = " << cmd << std::endl;
    //std::cout << "cmd-length de check_cmd = " << cmd.length() << std::endl;
    //std::cout << "keyword-length de check_cmd = " << key_word.length() << std::endl;
    //std::cout << "key_word in check_cmd = " << key_word << std::endl;
    while (j < 8)
    {
        if (key_word.compare(possible_cmd[j]) == 0)
        {
            ((*function[j])(data, i, cmd));
            return;
        }
        //std::cout << "possible_cmd[j] = " << possible_cmd[j] << std::endl;
        j++;
    }
    //std::cout << "cmd-length de check_cmd = " << possible_cmd->length() << std::endl;
    if (data->client[i].chanel.length() == 0)
    {
        //std::cout << "key_word in message = " << key_word << std::endl;
        //std::cout << "nickname in message = " << data->client[i].nickname << std::endl;
        std::string msg = "421: ";
        msg += data->client[i].nickname;
        msg += " ";
        msg += key_word;
        msg += " :Unknown command";
        create_output(data, msg);
        send_one_user(data, i);
        return;
    }
    else
    {
        std::string msg = data->client[i].nickname;
        msg += ": ";
        msg += cmd;
        create_output(data, msg);
        send_all_user(data, i);
    }
}

