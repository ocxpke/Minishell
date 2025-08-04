# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:34:30 by pabmart2          #+#    #+#              #
#    Updated: 2025/08/01 13:18:19 by pabmart2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB_DIR = include
NAME = libft.a

SRC = \
	src/ft_atoi.c \
	src/ft_atol.c \
	src/ft_bzero.c \
	src/ft_calloc.c \
	src/ft_errfree.c \
	src/ft_extractm.c \
	src/ft_free.c \
	src/ft_get_next_line.c \
	src/ft_getenv.c \
	src/ft_isalnum.c \
	src/ft_isalpha.c \
	src/ft_isascii.c \
	src/ft_isdigit.c \
	src/ft_isprint.c \
	src/ft_isspace.c \
	src/ft_itoa.c \
	src/ft_lstadd_back.c \
	src/ft_lstadd_front.c \
	src/ft_lstclear.c \
	src/ft_lstdelone.c \
	src/ft_lstindex.c \
	src/ft_lstiter.c \
	src/ft_lstlast.c \
	src/ft_lstmap.c \
	src/ft_lstnew.c \
	src/ft_lstsize.c \
	src/ft_matrix_free.c \
	src/ft_matrix_len.c \
	src/ft_matrix_mincol.c \
	src/ft_matrix_maxcol.c \
	src/ft_memchr.c \
	src/ft_memcmp.c \
	src/ft_memcpy.c \
	src/ft_memjoin.c \
	src/ft_memmove.c \
	src/ft_memset.c \
	src/ft_mindbl.c \
	src/ft_minint.c  \
	src/ft_nothing.c \
	src/ft_perror.c \
	src/ft_putchar_fd.c \
	src/ft_putendl_fd.c \
	src/ft_putnbr_fd.c \
	src/ft_putstr_fd.c \
	src/ft_split.c \
	src/ft_splitkeep.c \
	src/ft_splitm.c \
	src/ft_realloc.c \
	src/ft_strchr.c \
	src/ft_strchrm.c \
	src/ft_strdup.c \
	src/ft_strinsert.c \
	src/ft_striteri.c \
	src/ft_strjoin.c \
	src/ft_strlcat.c \
	src/ft_strlcpy.c \
	src/ft_strlen.c \
	src/ft_strmapi.c \
	src/ft_strncmp.c \
	src/ft_strndup.c \
	src/ft_strnstr.c \
	src/ft_strrchr.c \
	src/ft_strtkns.c \
	src/ft_strtrim.c \
	src/ft_substr.c \
	src/ft_tolower.c \
	src/ft_toupper.c \
	src/ft_uintptrtob.c \
	src/ft_uitoa.c \
	src/ft_uitob.c \

OBJ = $(SRC:.c=.o)

INCLUDES = \
	-Iinclude \
	-Iinclude/ft_get_next_line \

all: $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(LIB_DIR)/$(NAME)

re: fclean
	$(MAKE) all

$(NAME) : $(OBJ)
	@mkdir -p $(LIB_DIR)
	@ar rcs $(LIB_DIR)/$(NAME) $(OBJ)
	@echo "\033[32m\n¡$(NAME) compiled! \
    ᕦ(\033[36m⌐■\033[32m_\033[36m■\033[32m)ᕤ\n\033[0m"


$(OBJ): %.o : %.c
	@echo "\033[34mCompiling $<\033[0m"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all clean fclean re bonus
