FILE_C =	help_fun_1.c help_fun_3.c\
			help_fun_2.c main.c

FILE_O = $(FILE_C:.c=.o)

FILE_CB =	get_next_line_bonus.c get_next_line_utils_bonus.c\
			help_fun4_bonus.c help_fun_1_bonus.c\
			help_fun_2_bonus.c help_fun_3_bonus.c\
			main_bonus.c

FILE_OB = $(FILE_CB:.c=.o)

NAME = pipex

NAMEB = pipex_bonus

CC = cc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(FILE_O)
	$(CC) $(CFLAGS) $(FILE_O) -o $(NAME)

bonus:$(NAMEB)

$(NAMEB):$(FILE_OB)
	$(CC) $(CFLAGS) $(FILE_OB) -o $(NAMEB)

clean:
	rm -f $(FILE_O) $(FILE_OB)

fclean: clean
	rm -f $(NAME) $(NAMEB)

re: fclean all


