CC = cc
CFLAGS = -O3 -Wall -Wextra -Werror -g3 #-fsanitize=address
NAME = Folder_Sync_C

SRCS = ./src/main.c ./src/utils.c ./src/logs.c ./src/data_init.c ./src/sync.c ./src/exit.c ./src/signals.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:	
		rm -rf $(OBJS)

fclean:	clean
		rm -rf $(NAME)

re:	fclean all
