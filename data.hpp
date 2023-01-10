class data;
#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <map>
#include <vector>
#include "client.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


typedef struct s_data
{
    std::vector<client> client;
    std::string         pwd_server;
    std::string         server_name;
    std::string         input;

    int                 max_client;
    char                output[512];

}                       t_data;

typedef void(*funtab) (t_data *data, int i, std::string cmd);

int         create_new_client(int socketfd, t_data *data, sockaddr_in serv_addr);
int         first_parsing(t_data *data, int i);
int         buffer_check(t_data *data, int i);
void        check_cmd(t_data *data, int i, std::string key_word, std::string cmd);

// COMMANDE
void        pass(t_data *data, int i, std::string cmd);
void        nick (t_data *data, int i, std::string cmd);
void        user (t_data *data, int i, std::string cmd);
void        notice(t_data *data, int i, std::string cmd);
void        join (t_data *data, int i, std::string cmd);
void        create_output(t_data *data, std::string msg);
void        quit(t_data *data, int i, std::string cmd);
void        privmsg(t_data *data, int i, std::string cmd);
void        list(t_data *data, int i, std::string cmd);
void        kick(t_data *data, int i, std::string cmd);
void        cap(t_data *data, int i, std::string cmd);
void        ping(t_data *data, int i, std::string cmd);
void        ison(t_data *data, int i, std::string cmd);


// UTILS
std::string toUpper(std::string s);
void        ft_bzero(void *s, size_t n);
void        get_host_name(t_data *data);
char *      ft_strcpy(char *dest, const char * src);
int	        ft_atoi(const char *str);
size_t	    ft_strlen(const char *str);

void        send_all_user(t_data *data, int i);
void        send_one_user(t_data *data, int i);
void        message_compose(int num_args, ...);

#endif