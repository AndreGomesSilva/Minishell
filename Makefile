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

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

bonus: all

clean:
	$(MAKE) clean -C $(SRC_DIR_LIB)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(SRC_DIR_LIB)
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re