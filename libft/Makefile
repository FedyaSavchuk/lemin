LIBFT_FILES = ft_memset \
		ft_bzero \
		ft_memcpy \
		ft_memccpy \
		ft_memmove \
		ft_memchr \
		ft_memcmp \
		ft_strlen \
		ft_strdup \
		ft_strcpy \
		ft_strncpy \
		ft_strcat \
		ft_strncat \
		ft_strlcat \
		ft_strchr \
		ft_strrchr \
		ft_strrev \
		ft_strstr \
		ft_strnstr \
		ft_strcmp \
		ft_strncmp \
		ft_atoi \
		ft_itoa_base \
		ft_uitoa_base \
		ft_abs \
		ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_toupper \
		ft_tolower \
		ft_memalloc \
		ft_memdel \
		ft_strnew \
		ft_strdel \
		ft_strclr \
		ft_striter \
		ft_striteri \
		ft_strmap \
		ft_strmapi \
		ft_strequ \
		ft_strnequ \
		ft_strsub \
		ft_strjoin \
		ft_strjoinfree \
		ft_strtrim \
		ft_strsplit \
		ft_itoa \
		ft_putchar \
		ft_putchars \
		ft_putnbr \
		ft_putstr \
		ft_putendl \
		ft_putchar_fd \
		ft_putnbr_fd \
		ft_putstr_fd \
		ft_putendl_fd \
		ft_lstnew \
		ft_lstdelone \
		ft_lstdel \
		ft_lstadd \
		ft_lstiter \
		ft_lstmap \
		ft_strlcpy \
		ft_isspace

SRC_ALL  = $(addsuffix .c, $(LIBFT_FILES))
OBJ_ALL  = $(addsuffix .o, $(LIBFT_FILES))

DIR_INC   		= ./includes

CC              = gcc
NAME            = libft.a
#CFLAGS          = -Wall -Werror -Wextra -O2 -I$(DIR_INC)
CFLAGS          = -O2 -I$(DIR_INC)

all: $(NAME)

$(OBJ_ALL):
	@$(CC) -c $(CFLAGS) $(SRC_ALL)

$(NAME): $(OBJ_ALL)
	@ar rc $(NAME) $?
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ_ALL)

fclean: clean
	@rm -f $(NAME)

re: fclean all

compile: re
	$(CC) main $(NAME) -I$(DIR_INC)
