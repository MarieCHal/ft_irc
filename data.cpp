#include "data.hpp"

void check_cmd(t_data *data, int i, std::string key_word, std::string cmd)
{
    //std::cout << "key_word de check_cmd = " << key_word << std::endl;
    std::string possible_cmd [] = {"NICK", "USER", "JOIN"};
    funtab function[] = {&nick, &user, &join};
    size_t j = 0;
    std::cout << "keyword-length de check_cmd = " << key_word.length() << std::endl;
    std::cout << "key_word in check_cmd = " << key_word << std::endl;
    while (j < possible_cmd->length())
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
    message(data, i, cmd, key_word);
}