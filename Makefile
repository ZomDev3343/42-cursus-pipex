SRC=pipex.c \
	utils.c \
	cmd_util.c
BONUS_SRC=pipex_bonus.c \
	utils.c \
	cmd_util.c \
	utils_bonus.c
OBJ=$(SRC:.c=.o)
BONUS_OBJ=$(BONUS_SRC:.c=.o)
BONUS=pipex_bonus
NAME=pipex
FT=libft/libft.a
FLAGS=-Wall -Wextra -Werror

all:
	make -C libft
	make $(NAME)

%.o: %.c
	cc -c $< -o $@

$(NAME): $(FT) $(OBJ)
	cc $(FLAGS) $(FT) $(OBJ) -o $@

bonus: $(BONUS_OBJ)
	make -C libft
	cc $(FLAGS) $(FT) $(BONUS_OBJ) -o $(BONUS)

clean:
	rm -rf *.o
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: clean all

.PHONY: all clean fclean re
