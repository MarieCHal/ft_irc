#include "data.hpp"

int interpretor(t_data *data, int i, std::string cmd)
{
    size_t pos;
    std::string key_word;
    cmd.erase(cmd.length() - 2, cmd.length());
    cmd[cmd.length()] = '\0';
    pos = cmd.find(' ');
    if (pos != std::string::npos)
        pos = cmd.find_first_of(32, 0);
    else
        pos = cmd.find_first_of('\0', 0);
    key_word.assign(cmd, 0, pos);
    key_word = toUpper(key_word);
    check_cmd(data, i, key_word, cmd);
    return (0);
}

int first_parsing(t_data *data, int i)
{
    size_t pos;
    std::string to_parse(data->input);
    std::string cmd;
    std::cout << "input = " << data->input << std::endl;
    while (to_parse.length() != 0)
    {
        pos = to_parse.find_first_of('\n', 0);
        cmd.assign(to_parse, 0, pos + 1);
        interpretor(data, i, cmd);
        to_parse.erase(0, pos + 1);
    }
    return (0);
}