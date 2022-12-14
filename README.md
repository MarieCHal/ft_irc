# ft_irc
Creation of an IRC server

# summary of the project
Creation of an Internet Relay Chat in C++98.
- We don't need to create client.
- the program takes as argument the number of the port on 
which our server will accept connexions and a password with 
which the client identify themselves to the server.
- the Server can manage multiple clients
- no forking
- only use one poll() (or select())
- The communcation protocol is TCP/IP
- only the following features of official IRC server have to be implemented: 

        - a client can authentify its self, 
            define a NICKNAME, a USERNAME, JOIN a channel, 
            send and recieve private messages. 
        - all the messages send on a channel have to be 
            send to all client that have joined it.
        - we must implement operators


# Clarification
take a look at: http://abcdrfc.free.fr/rfc-vf/rfc1459.html
            https://www.ionos.com/digitalguide/server/know-how/irc/

SERVER: a node on which the clients can connect and communicate with each other. 

CLIENT: anything that connect to the server that is not a server. 
--> each client has a nickname
--> the server has to know the real name of the host on which the client is 
    executed, the name of the user of the client on that host.

OPERATORS : An IRC operator is a user on an IRC network that has privileged access. 
    They are in charged with the task of enforcing the network 
        rules and can execute certain functions:
- connect and deconnect servers (to prevent bad routing)
- 


CHANNEL: “place” where the users will be able to be identified and communicate, 
            all the sent messages have to be communicated  to all users connected to the channel.

    CHARACTERISTICS:
    - channel's name start with: '&' or '#' 
        and is max 200 char. long
        doesn't contain spaces, control G or ','. 

    JOIN A CHANNEL:

    CREATING A NEW CHANNEL:


CHANNEL OPERATORS: 'owners of the channel

# How sockets work
src: https://www.ibm.com/docs/en/i/7.1?topic=programming-how-sockets-work

On server side:
1. A socket (endpoint for communication) is created.                    --> socket()
2. The socket has to be bind() to give a unique name to the sokcket,    --> bind()
    the server must bind a name to be accessible from the network.     
3. The server is then listening, meaning it will accept client          --> listen()
    connexion requests. 
4. If a client tries to connect to the server the server can allow it   --> accept()
    using accept.
5. data transfer through API.   
6. when server or client wahts to stop operations: close                --> close()



# The protocol

ESTABLISHING A CONNEXION

    commands required to establish a connexion between a server and a client 
        (there more of them but we only need to implement these)
        cmd PASS: connexion password (4.1.1)
            -> PASS <password>
            -> Numerical answers:
            ERR_NEEDMOREPARAMS                   ERR_ALREADYREGISTRED

        cmd NICK: used to give a nickname to a user or change one.
            -> NICK <nickname> [<comptor distance>]
                - the comptor distance is only used by the server and doesn't 
                    have to be filled by the user. It indicates the the distance 
                    between the client and the server (local = 0)
            -> specific behaviours if a server recieves a nick with an already 
                existing nickname.
            -> Numerical answers: 
                ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
                ERR_NICKNAMEINUSE               ERR_NICKCOLLISION


        cmd USER : used to start a connexion
            -> USER <user name> <host> <server name> <real name>
            -> when cmd user comes directly from a client the host name and the 
                server name are generally ignored. 

                            ---

SENDING A PRIVATE MESSAGE
    
    cmd PRIVMSG: used ot send messages between users 

# Authorized functions
[srcs:]( https://pubs.opengroup.org/onlinepubs/009604499/functions/)
        https://www.ibm.com/docs/en/i/7.1?topic=programming-how-sockets-work

`socket`: int socket(int domain, int type, int protocol);
    -> creates a socket
    domain: communication domain, (AF_INET)
    type: type of communication desired (SOCK_STREAM)
    protocol: the protocol to be used (IPPROTO_TCP or 0)
    return: fd that can be used to operate on the socket (-1 failed).

`setsockopt`: 
    helps in manipulating options for the socket
`getsockname`:
`getprotobyname`:
`gethostbyname`:
getaddrinfo:
freeaddrinfo:
`bind`: int bind(int socket_descriptor, struct sockaddr *local_address, 
            int address_length)
    -> set local address for socket


connect: connect the socket to the address of the server
`listen`: int listen(int socket_descriptor, int back_log)
    -> puts the server in a passive mode where it listens for connections (server)
    socket_des: the socket that has to be prepared to recieved cnnexion
    back_log: The maximum number of connection requests that can be queued before   
                the system starts rejecting incoming requests. 
    return: 0 or -1

accept: the server can accept client connexions
htons: 
htonl:
ntohs:
ntohl:
inet_addr:
inet_ntoa:
send: sends infos
recv: 
signal:
lseek:
fstat:
fcntl:
poll (or other ike select()):

# To do
COMMANDs:
    - PASS
    - NICK
    - USER

# look up
- C/N lines for servers and I lines for clients (4.1.1)

# Questioning ??
- What kind of operator (channel operators?) do we have to implement (how many commands?
- Do we have to apply the exacte same rules? (ex. channel names and syntaxes?)
- sockadrr and sockaddr_in

# some ideas and definitions
srcs: https://www.geeksforgeeks.org/socket-programming-cc/


- Socket Programming: a way of connecting two nodes on a network to communicate with each other. Server socket 'listen' on a particular port while client socket reaches out to the others. 


- Network nodes: connection point among network devices like routers, printers or switches (or client and server) that can receive and send data from one endpoint to the other.

- Port: virtual point where network connection takes place. Each port is associated with a specific process or service. IP addresses allow communication between specific devices while port numbers allow targeting a specific service within the device. (the IP address if the street number and the network is the floor).

- socket: one endpoint (node) of a two way communication link between two programs running on the network, listening on a specific port. Each socket has a specific address (IP address and port number). Generally used in server client services (the client creates a socket and tries to connect to the server socket). When the connection is established data transfer can take place.

- TCP: Transport control protocol. Rearranges data packets (units of data that travel along a given network path, also contains routing info) so that it can be transmitted between client and server, it guarantees that the integrity of the data has been transferred. 
→ TCP establishes and maintains connection throughout the communication, manages flow control, organization of data packages and ensures all the packets reach their destination.

- IP: Internet Protocol. method for sending data from one device to another across the internet.

- TCP/IP: Protocol suite. IP obtains and defines the address of the destination, TCP is responsible for transporting and routing the data through the network as well as ensuring that it did reach the wanted target.
