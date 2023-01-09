#include "data.hpp"

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