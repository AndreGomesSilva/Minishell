NAME = minishell
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
INC = -I./include

# file path #
SRCS_DIR = src/
NODE = handle_nodes
MATRIX = handle_matrix
LEXER = handle_lexer

OBJS_DIR = obj/
SRC_DIR_LIB= ./libft
LIB = ./libft/libft.a -lreadline

FILES = main \
		$(NODE)/create_main_node \
		$(NODE)/free_lst \
		$(MATRIX)/free_matrix \
		$(LEXER)/token_factory \

OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(SRC_DIR_LIB) --no-print-directory
	$(CC) $(OBJS) $(LIB) $(CFLAGS) $(INC) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)$(NODE)
	@mkdir -p $(OBJS_DIR)$(MATRIX)
	@mkdir -p $(OBJS_DIR)$(LEXER)

runTests:
	@$(MAKE) -C $(SRC_DIR_LIB) --no-print-directory
	g++ src/exemplo.c tests/exemplo_test.cpp tests/main.cpp -I/usr/local/include -L/usr/local/lib -lgtest -lgtest_main $(LIB) $(CFLAGS) $(INC) -o test
	./test

bonus: all

clean:
	$(MAKE) clean -C $(SRC_DIR_LIB)
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(MAKE) fclean -C $(SRC_DIR_LIB)
	$(RM) $(NAME)
	$(RM) test

re: fclean all

.PHONY: all bonus clean fclean re