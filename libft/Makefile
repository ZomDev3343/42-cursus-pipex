PRINTF= printf/conversion.c \
		printf/ft_printf.c \
		printf/printer.c \
		printf/printer_2.c \
		printf/put_util.c \
		printf/util.c \
		printf/util2.c \
		printf/format.c
SRC=ft_split.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_isdigit.c \
	ft_strlen.c \
	ft_split.c \
	ft_atol.c \
	ft_error.c \
	ft_strcmp.c \
	ft_strjoin.c \
	ft_swap.c \
	$(PRINTF)
OBJ= $(SRC:.c=.o)
NAME=libft.a

all: $(NAME)

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)

%.o: %.c
	gcc -c -Wall -Werror -Wextra $< -o $@

clean:
	rm -rf *.o
	rm -rf */*.o

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all clean fclean re
