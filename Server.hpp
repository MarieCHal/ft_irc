
/** La classe server contient:
 *  un tableau de users
 * les channels actifs
 * 
 * member functions:
 * 
 * check if a user exists
 * check the right of a given user
 * check if a channel exists
 * creates a new chanel
 * check if the chanell has to be removed (est ce que le dernier 
 *          user est partit)
 *
 * fonction qui etablit la connexion peut etre une fonction membre
 * ou pas c'est egal
 * 
 * 
 * quand est ce que ca finit:
 * quand le serveur envoie `quit` le serveur close la socket en relation
 * avec le user
 * quand le serveur est arrete toute le sockt doivent etre close (leaks)
 * 
 * */

#ifndef SERVER_HPP
#define SERVER_HPP

class server
{

};

#endif

