SRC=pipex.c \
	utils.c \
	cmd_util.c
BONUS_SRC=pipex_bonus.c \
	utils.c \
	cmd_util.c \
	here_doc.c \
	utils_bonus.c
OBJ=$(SRC:.c=.o)
BONUS_OBJ=$(BONUS_SRC:.c=.o)
BONUS=bonus
NAME=pipex
FT=libft/libft.a
FLAGS=-Wall -Wextra -Werror -g

all:
	make -C libft
	make $(NAME)

%.o: %.c
	cc $(FLAGS) -g -c $< -o $@

$(NAME): $(OBJ)
	cc $(FLAGS) $(OBJ) $(FT) -o $@

$(BONUS): $(BONUS_OBJ)
	make -C libft
	cc $(FLAGS) $(BONUS_OBJ) $(FT) -o $(BONUS)

clean:
	rm -rf *.o
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BONUS)
	make fclean -C libft

re: clean all

.PHONY: all clean fclean re
