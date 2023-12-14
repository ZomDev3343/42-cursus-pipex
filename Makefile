SRC=pipex.c \
	utils.c
BONUS_SRC=pipex_bonus.c
OBJ=$(SRC:.c=.o)
NAME=pipex
FT=libft/libft.a
FLAGS=-Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	cc -c $< -o $@

$(NAME): $(OBJ)
	make -C libft
	cc $(FLAGS) $(FT) $(OBJ) -o $@

clean:
	rm -rf *.o
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: clean all

.PHONY: all clean fclean re
