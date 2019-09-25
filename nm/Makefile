NAME = nm
SRCS = src/nm.c src/x64.c src/utils.c
FLAGS = -Wall -Wextra -Werror
OBJS = ${SRCS:.c=.o}
HEADER = -I ./inc/
LIBS = -L. libft.a

all: $(NAME)

$(NAME):

.c.o:
	gcc $(FLAGS) $(HEADER) -c $< -o $@

$(NAME): $(OBJS)
	gcc $(OBJS) $(LIBS) -o $(NAME)

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
