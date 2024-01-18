NAME = ft_strace
EXEC = $(PWD)/$(NAME)

CC = gcc
FLAGS = -Wall -Wextra -Werror -g3
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all \
					 --track-fds=yes --trace-children=yes

SRC_PATH = src/
OBJ_PATH = obj/
HEADERS = -Iinclude

SRC_NAME =	main.c	 \
						child.c	 \
						tracer.c \
						print.c  \
						utils.c  \
						set_str_params_to_regs.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(@D)
	$(CC) $(FLAGS) $(HEADERS) -MMD -c $< -o $@

-include $(OBJ:%.o=%.d)

run: all
	$(EXEC) $(bin)

valgrind: all
	$(VALGRIND) $(EXEC) $(bin)

all: $(NAME)

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re run valgrind
