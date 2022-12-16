
/** reçois une string (read depuis la socket())
 * elle est transise par la partie connexion (socket programming)
 * fait un premier parsing, est ce que c'est un message ou une commande
 * dans le cas d'une commande trouve la bonne
 * 
 * check if it is a valid command
 * contient un tableau avec les commandes possible
 * 
 * contient des fonctions communes a toutes les commandes
 * (ex. nombre d'arguments, nombre max)
 * */