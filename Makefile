NAME = minishell
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
INC = -I./include

# file path #
SRCS_DIR 	= src/
TEST_DIR 	= test/
LIST 		= list
MATRIX 		= matrix
LEXER 		= lexer
EXPANDER    = expander
PARSER 		= parser
HASHTABLE	= hashtable
BUILTIN		= builtin

OBJS_DIR 	= obj/
SRC_DIR_LIB	= ./libft
LIB 		= ./libft/libft.a -lreadline

FILES_WITHOUT_MAIN = \
	handle_config handle_signal	middleware \
	handle_errors handle_free \
	$(LIST)/handle_list_cmd $(LIST)/handle_list_arg \
	$(LEXER)/handle_token $(LEXER)/handle_type $(LEXER)/utils \
	$(EXPANDER)/handle_expander $(EXPANDER)/utils \
	$(HASHTABLE)/set_hash_table $(HASHTABLE)/aux_hash_function  \
	$(HASHTABLE)/utils $(HASHTABLE)/handle_hash_table \
	$(PARSER)/handle_matrix $(PARSER)/handle_parser \
	$(PARSER)/handle_path $(PARSER)/utils \
	$(PARSER)/handle_syntax_error \
#	$(BUILTIN)/handle_builtin $(BUILTIN)/export_unset_env_exit \
#	$(BUILTIN)/cd $(BUILTIN)/echo $(BUILTIN)/env \
#	$(BUILTIN)/exit $(BUILTIN)/export $(BUILTIN)/pwd \
#	$(BUILTIN)/unset $(BUILTIN)/handle_builtin \

FILES = \
	main $(FILES_WITHOUT_MAIN)

FILE_T = \
	main_test $(LEXER)/*
#	main_test $(LEXER)/* $(EXPANDER)/* $(HASHTABLE)/* $(PARSER)/* $(LIST)/*

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
	@mkdir -p $(OBJS_DIR)$(LIST)
	@mkdir -p $(OBJS_DIR)$(MATRIX)
	@mkdir -p $(OBJS_DIR)$(LEXER)
	@mkdir -p $(OBJS_DIR)$(EXPANDER)
	@mkdir -p $(OBJS_DIR)$(HASHTABLE)
	@mkdir -p $(OBJS_DIR)$(PARSER)
#	@mkdir -p $(OBJS_DIR)$(BUILTIN)
	@mkdir -p $(OBJS_DIR)handle_signal

runTests:
	@$(RM) testeRun	
	@$(MAKE) -C $(SRC_DIR_LIB) --no-print-directory
	g++ $(FILE_TESTE) $(FILE_TESTE_PROG) $(INC) -I/usr/local/include -L/usr/local/lib -lgtest -lgtest_main $(LIB) -o testRun
	./testRun

bonus: all

clean:
	$(MAKE) clean -C $(SRC_DIR_LIB)
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(MAKE) fclean -C $(SRC_DIR_LIB)
	$(RM) $(NAME)
	$(RM) testRun

re: fclean all

.PHONY: all bonus clean fclean re