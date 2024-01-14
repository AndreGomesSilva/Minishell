NAME = minishell
CC = cc -g
CFLAGS =
# CFLAGS = -Wall -Wextra -Werror
RM = rm -f
INC = -I./include

# file path #
SRCS_DIR 	= src/
TEST_DIR 	= tests/
NODE 		= handle_nodes
MATRIX 		= handle_matrix
LEXER 		= handle_lexer
EXPANDER    = handle_expander

OBJS_DIR 	= obj/
SRC_DIR_LIB	= ./libft
LIB 		= ./libft/libft.a -lreadline

FILES_WITHOUT_MAIN = \
	handle_start handle_signal \
	$(NODE)/create_node $(NODE)/free_lst \
	$(MATRIX)/handle_matrix \
	$(LEXER)/handle_token \
	$(LEXER)/handle_type \
	$(LEXER)/utils \
	$(EXPANDER)/handle_expander \
	$(EXPANDER)/utils \

FILES = \
	main $(FILES_WITHOUT_MAIN)

FILE_T = \
	main_test $(MATRIX)/handle_matrix_test \


FILE_TESTE 		= $(addprefix $(TEST_DIR), $(addsuffix .cpp, $(FILE_T)))
FILE_TESTE_PROG	= $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES_WITHOUT_MAIN)))

OBJS 			= $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

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
	@mkdir -p $(OBJS_DIR)$(EXPANDER)
	@mkdir -p $(OBJS_DIR)handle_signal

runTests:
	@$(MAKE) -C $(SRC_DIR_LIB) --no-print-directory
	g++ $(FILE_TESTE) $(FILE_TESTE_PROG) -I/usr/local/include -L/usr/local/lib -lgtest -lgtest_main $(LIB) $(CFLAGS) $(INC) -o test
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