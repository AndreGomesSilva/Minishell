NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
INC = -I./include
SRC_DIR = src
OBJS_DIR = obj
SRC_DIR_LIB= ./libft
LIB = ./libft/libft.a
FILES = main \
		create_main_node \

OBJS = $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(FILES)))

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(SRC_DIR_LIB) --no-print-directory
	$(CC) $(OBJS) $(LIB) $(CFLAGS) $(INC) -o $(NAME)

<<<<<<< HEAD
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
=======
runTests:
	@$(MAKE) -C $(SRC_DIR_LIB) --no-print-directory
	g++ src/exemplo.c tests/exemplo_test.cpp -I/usr/local/include -L/usr/local/lib -lgtest -lgtest_main $(LIB) $(CFLAGS) $(INC) -o test
	./test
>>>>>>> ce84393ce51829fd6ed105de30d929dde356b876

bonus: all

clean:
	$(MAKE) clean -C $(SRC_DIR_LIB)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(SRC_DIR_LIB)
	$(RM) $(NAME)
	$(RM) test

re: fclean all

.PHONY: all bonus clean fclean re