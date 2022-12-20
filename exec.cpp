#include "exec.hpp"

exec_input::exec_input(std::string inputcmd){

    this->_cmd = inputcmd;
}

void exec_input::check_cmd(t_data *data, int i, std::string cmd)
{
    std::string possible_cmd [] = {"NICK", "USER", "JOIN", "CAP"};
    exec_input::funtab function[] = {&exec_input::_nick, &exec_input::_user, &exec_input::_join, &exec_input::_join};
    int j = 0;
    while (cmd.compare(possible_cmd[j]) != 0)
        j++;
    ((this->*function[j])(data, i, cmd));
}

void    exec_input::_nick (t_data *data, int i, std::string copy_cmd) {
    std::cout << copy_cmd << data->max_client << i << std::endl;
    printf("\nNIIIIICK\n");
}
void    exec_input::_user (t_data *data, int i, std::string copy_cmd) {
    std::cout << copy_cmd << data->max_client << i << std::endl;   
    printf("\nUUUUUUUUSER\n");
}
void    exec_input::_join (t_data *data, int i, std::string copy_cmd) {
    std::cout << copy_cmd << data->max_client << i << std::endl;
    printf("\nJOIIIIIIIIiN\n");
}