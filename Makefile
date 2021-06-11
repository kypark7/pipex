NAME = pipex

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRC = ./pipex.c

OSRC = $(SRC:.c=.o)

all: $(NAME) $(OSRC)

$(NAME): $(SRC)
	@make -C libft 
	@cp libft/libft.a ./
	@gcc $(FLAGS) ./libft/libft.a  $(SRC) -o $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

clean:
	@make -C libft clean
	@rm -f $(OSRC)

fclean: clean
	@make -C libft fclean
	@rm -f libft.a
	@rm -f $(NAME)

re: fclean all


.PHONY: all  clean fclean re norm 