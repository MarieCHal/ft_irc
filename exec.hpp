#ifndef EXEC_HPP
#define EXEC_HPP
#include "data.hpp"

class exec_input
{
    public:
        typedef void(exec_input::*funtab) (t_data *data, int i, std::string copy_cmd);
        //exec_input::funtab function[3];
        //std::string possible_cmd[3];
        void    check_cmd(t_data *data, int i, std::string cmd);

    std::string _cmd;
    private:
        void    _nick (t_data *data, int i, std::string copy_cmd);
        void    _user (t_data *data, int i, std::string copy_cmd);
        void    _join (t_data *data, int i, std::string copy_cmd);

    public:
        exec_input() {}
        exec_input(std::string inputcmd);
        ~exec_input() {}
};

#endif