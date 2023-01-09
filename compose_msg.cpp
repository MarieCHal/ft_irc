#include "data.hpp"
//client a client
void compose_private_message(t_data *data, std::string param1, std::string param2, std::string mess)
{
    std::string msg = ":";
    msg += param1;
    msg += " PRIVMSG ";
    msg += param2;
    msg += " :";
    msg += mess;
    create_output(data, msg);
}
//reponse auto serveur client
void compose_reply(t_data *data, std::string err_no, std::string param, std::string mess)
{
    std::string msg = ":";
    msg += data->server_name;
    msg += err_no;
    msg += param;
    msg += mess;
    create_output(data, msg);
}
//du serveur au client
void compose_message(t_data *data, std::string keyword, std::string param1, std::string param2)
{
    std::string msg = ":";
    msg += param1;
    msg += keyword;
    msg += param2;
    create_output(data, msg);
}

void message_compose(int num_args, ...)
{
    va_list args;
    std::string msg = ":";
    t_data *tmp_data;

    va_start(args, num_args);
    for (int i = 0; i < num_args; i++)
    {
        if (i == 0)
            tmp_data = va_arg(args, t_data*);
        else
        {
            char* tmp = va_arg(args, char*);;
            msg += tmp;
        }
    }
    create_output(tmp_data, msg);
    va_end(args);
}