NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
INC = -I./include
SRC_DIR = ./src
SRC_DIR_LIB= ./libft
LIB = ./libft/libft.a
FILES = main

OBJS = $(addprefix $(SRC_DIR)/, $(addsuffix .o, $(FILES)))

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS)
	@$(MAKE) -C $(SRC_DIR_LIB) --no-print-directory
	$(CC) $(OBJS) $(LIB) $(CFLAGS) $(INC) -o $(NAME)

bonus: all

clean:
	$(MAKE) clean -C $(SRC_DIR_LIB)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(SRC_DIR_LIB)
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re