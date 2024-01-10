PRINTF= printf/conversion.c \
		printf/ft_printf.c \
		printf/printer.c \
		printf/printer_2.c \
		printf/put_util.c \
		printf/util.c \
		printf/util2.c \
		printf/format.c
GNL=gnl/get_next_line_bonus.c \
	gnl/get_next_line_utils_bonus.c
SRC=ft_split.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_isdigit.c \
	ft_strlen.c \
	ft_split.c \
	ft_atol.c \
	ft_error.c \
	ft_strcmp.c \
	ft_strcpy.c \
	ft_strjoin.c \
	ft_strnstr.c \
	ft_swap.c \
	$(PRINTF) \
	$(GNL)
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
