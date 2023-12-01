NAME=libft.a
CC=cc
CFLAGS=-Wall -Wextra -Werror
RM = rm -f
INC = -I./include

FILES_LIB = ft_isalpha  ft_isdigit  ft_isalnum  ft_isascii  ft_isprint  \
		ft_strlen  ft_memset  ft_bzero  ft_memcpy  ft_memmove  \
		ft_strlcpy  ft_strlcat  ft_toupper  ft_tolower  ft_strchr  \
		ft_strrchr  ft_strncmp  ft_memchr  ft_memcmp  ft_strnstr  \
		ft_atoi  ft_calloc  ft_strdup  ft_substr  ft_strjoin  \
		ft_strtrim  ft_split  ft_itoa  ft_strmapi  ft_striteri  \
		ft_putchar_fd  ft_putstr_fd  ft_putendl_fd  ft_putnbr_fd
FILES_GNL = get_next_line get_next_line_utils
FILES_PRINTF = ft_printf printf_utils

SRC_DIR_LIB = src/
SRC_DIR_GNL = gnl/
SRC_DIR_PRINTF = printf/

OBJ_LIB = $(addprefix $(SRC_DIR_LIB), $(addsuffix .o, $(FILES_LIB)))
OBJ_PRINTF = $(addprefix $(SRC_DIR_PRINTF), $(addsuffix .o, $(FILES_PRINTF)))
OBJ_GNL = $(addprefix $(SRC_DIR_GNL), $(addsuffix .o, $(FILES_GNL)))

all: $(NAME)

$(NAME): $(OBJ_LIB) $(OBJ_PRINTF) $(OBJ_GNL)

%.o: %.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@
	ar rcs $(NAME) $@

clean:
	rm -f $(OBJ_LIB) $(OBJ_PRINTF) $(OBJ_GNL)

fclean: clean
	$(RM) $(NAME)

re:	clean all

.PHONY:	all clean fclean re
