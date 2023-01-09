/** @brief sorte de base de donnee
 * fait le lien entre le main (la recuperation des donnees)
 * et le code d'analyise et d'execution a faire afin de 
 * renvoyer une reponse ou d'executer la demmande du client
 * 
 * attributs:
 * - tableu de client
 * - tableau de pointeur sur objet channel (vectoro f vector)
 *      -> pos [0] = password
 *      -> commence a pos 1 pour stocker les sockets
 * - 
 * 
 * attributs:
 * - input message
 * - outpus message (peutetre pas ici)
 * */

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
    std::string pwd_server;
    std::string server_name;
    std::vector<client> client; // le tableau des clients
    //std::map<std::string, std::vector<int> > chanels; // les objets 
    int     max_client;

    std::string input;
    //char input[512];
    char output[512];

}       t_data;

typedef void(*funtab) (t_data *data, int i, std::string cmd);

int create_new_client(int socketfd, t_data *data, sockaddr_in serv_addr);
int first_parsing(t_data *data, int i);
int buffer_check(t_data *data, int i);

void    pass(t_data *data, int i, std::string cmd);
void    nick (t_data *data, int i, std::string cmd);
void    user (t_data *data, int i, std::string cmd);
void    notice(t_data *data, int i, std::string cmd);
void    join (t_data *data, int i, std::string cmd);
void    check_cmd(t_data *data, int i, std::string key_word, std::string cmd);
void    ft_bzero(void *s, size_t n);
std::string toUpper(std::string s);


//gael

void    create_output(t_data *data, std::string msg);
void    message (t_data *data, int i, std::string cmd, std::string key_word);
void    send_all_user(t_data *data, int i);
void    send_one_user(t_data *data, int i);
char *  ft_strcpy(char *dest, const char * src);
void    privmsg(t_data *data, int i, std::string cmd);
void    quit(t_data *data, int i, std::string cmd);
void list(t_data *data, int i, std::string cmd);
int	ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
void kick(t_data *data, int i, std::string cmd);
void cap(t_data *data, int i, std::string cmd);
void get_host_name(t_data *data);
void ping(t_data *data, int i, std::string cmd);
void ison(t_data *data, int i, std::string cmd);
void message_compose(int num_args, ...);

//rpl/err/mess
void compose_reply(t_data *data, std::string err_no, std::string param, std::string mess);
void compose_message(t_data *data, std::string keyword, std::string param1, std::string param2);
void compose_private_message(t_data *data, std::string param1, std::string param2, std::string mess);

#endif