NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
INC = -I./include
# file path #
SRCS_DIR = src/
NODE = handle_nodes

OBJS_DIR = obj/
SRC_DIR_LIB= ./libft
LIB = ./libft/libft.a

FILES = main \
		$(NODE)/create_main_node \

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(notdir $(FILES))))

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(SRC_DIR_LIB) --no-print-directory
	$(CC) $(OBJS) $(LIB) $(CFLAGS) $(INC) -o $(NAME)

$(OBJS): $(SRCS) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

runTests:
	@$(MAKE) -C $(SRC_DIR_LIB) --no-print-directory
	g++ src/exemplo.c tests/exemplo_test.cpp -I/usr/local/include -L/usr/local/lib -lgtest -lgtest_main $(LIB) $(CFLAGS) $(INC) -o test
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