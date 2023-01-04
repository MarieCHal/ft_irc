NAME = irc_server

CC = c++

CFLAGS = -Wextra -Werror -Wall -std=c++98

AR = ar -rc

SRCS_DIR = ./src
OBJS_DIR = ./objs

SRCS =	main.cpp \
		init_client.cpp \
		parse.cpp \
		data.cpp \
		fonction_utils.cpp \
		message.cpp \
		nick.cpp \
		user.cpp \
		join.cpp \
		send.cpp \
		quit.cpp

			
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.cpp=.o)))

vpath %.c $(SRCS_DIR)

RM = rm -f

.PHONY: all re clean fclean debug

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o : %.cpp | $(OBJS_DIR)
	$(CC) $(CFLAGS) -o $@ -c $^

clean :
	$(RM) -r $(OBJS_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all