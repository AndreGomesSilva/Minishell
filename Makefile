NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
INC = -I./include

SRCS_DIR 	= src/
TEST_DIR 	= test/
LIST 		= list
MATRIX 		= matrix
LEXER 		= lexer
EXPANDER    = expander
PARSER 		= parser
HASHTABLE	= hashtable
BUILTIN		= builtin
EXECUTOR	= executor
HEREDOC		= heredoc

OBJS_DIR 	= obj/
SRC_DIR_LIB	= ./libft
LIB 		= ./libft/libft.a -lreadline

FILES_WITHOUT_MAIN = \
	handle_config handle_signal	middleware \
	handle_errors handle_free \
	$(LIST)/handle_list_cmd $(LIST)/handle_list_arg \
	$(LEXER)/handle_token $(LEXER)/handle_type \
	$(LEXER)/handle_quotes $(LEXER)/utils \
	$(EXPANDER)/handle_expander $(EXPANDER)/utils $(EXPANDER)/aux_expander \
	$(HASHTABLE)/utils $(HASHTABLE)/handle_hash_table $(HASHTABLE)/handle_env_matrix\
	$(HASHTABLE)/set_hash_table $(HASHTABLE)/aux_hash_function  \
	$(PARSER)/handle_matrix $(PARSER)/handle_parser \
	$(PARSER)/handle_path $(PARSER)/utils \
	$(PARSER)/handle_syntax_error $(PARSER)/handle_parser_cont \
	$(EXECUTOR)/handle_redirects $(EXECUTOR)/handle_execution\
	$(EXECUTOR)/handle_io $(EXECUTOR)/handle_pipes $(EXECUTOR)/handle_fds \
	$(EXECUTOR)/handle_multi_execution $(EXECUTOR)/utils \
	$(BUILTIN)/handle_builtin $(BUILTIN)/echo \
	$(BUILTIN)/cd $(BUILTIN)/env \
	$(BUILTIN)/exit $(BUILTIN)/export  $(BUILTIN)/exit_util \
	$(BUILTIN)/unset \
	$(BUILTIN)/pwd \
	$(HEREDOC)/handle_heredoc $(HEREDOC)/utils $(HEREDOC)/print_heredoc_error \

FILES = \
	main $(FILES_WITHOUT_MAIN)

FILE_T = \
	main_test $(LEXER)/*

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
	@mkdir -p $(OBJS_DIR)$(EXECUTOR)
	@mkdir -p $(OBJS_DIR)$(BUILTIN)
	@mkdir -p $(OBJS_DIR)$(HEREDOC)
	@mkdir -p $(OBJS_DIR)handle_signal

runTests:
	@$(RM) testeRun	
	@$(MAKE) -C $(SRC_DIR_LIB) --no-print-directory
	g++ $(FILE_TESTE) $(FILE_TESTE_PROG) $(INC) -I/usr/local/include -L/usr/local/lib -lgtest -lgtest_main $(LIB) -o testRun
	./testRun

bonus: all

clean:
	$(MAKE) clean -C $(SRC_DIR_LIB)
	$(RM) -r $(OBJS_DIR) ./heredoc

fclean: clean
	$(MAKE) fclean -C $(SRC_DIR_LIB)
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
