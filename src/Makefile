# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/30 19:30:00 by pablo             #+#    #+#              #
#    Updated: 2025/07/31 16:12:02 by jose-ara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable de pruebas
NAME = minishell

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Directorios
ROOTDIR = ..
SRCDIR = .
LIBFTDIR = $(ROOTDIR)/lib/libft
INCDIR = $(ROOTDIR)/include
OBJDIR = obj

# Archivos fuente del parser (excluyendo main.c)
PARSER_SRCS = $(SRCDIR)/parse/parser.c \
              $(SRCDIR)/parse/parser_cmd_resolver.c \
              $(SRCDIR)/parse/parser_env.c \
              $(SRCDIR)/parse/parser_split_args.c \
              $(SRCDIR)/parse/parser_split_pipes.c \
              $(SRCDIR)/parse/parser_split_quote.c \
              $(SRCDIR)/parse/parser_tokenization.c \
              $(SRCDIR)/parse/utils/parser_clean_splitted.c \
              $(SRCDIR)/parse/utils/parser_collapse.c \
              $(SRCDIR)/parse/utils/parser_free_tokens.c\
			  $(SRCDIR)/main.c

SIGNALS_SRCS = $(SRCDIR)/signals/signals.c

# Todos los archivos fuente
ALL_SRCS = $(PARSER_SRCS) $(SIGNALS_SRCS)

# Archivos objeto
OBJS = $(ALL_SRCS:%.c=$(OBJDIR)/%.o)

# Libft
LIBFT = $(LIBFTDIR)/include/libft.a

# Flags de inclusión
INCLUDES = -I$(INCDIR) -I$(LIBFTDIR)/include -I$(LIBFTDIR)/include/ft_get_next_line -I$(LIBFTDIR)/include/ft_printf

# Regla principal
all: $(NAME)

# Crear directorio de objetos
$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(SRCDIR)/parse
	@mkdir -p $(OBJDIR)/$(SRCDIR)/parse/utils
	@mkdir -p $(OBJDIR)/parser
	@mkdir -p $(OBJDIR)/utils
	@mkdir -p $(OBJDIR)/signals

# Compilar archivos objeto
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@ -lreadline
# -MMD -MP ????????

# Compilar libft
$(LIBFT):
	@echo "Compiling libft..."
	@make -C $(LIBFTDIR)

# Compilar el programa de pruebas
$(NAME): $(OBJS) $(LIBFT)
	@echo "Linking parser tests..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "Parser test suite compiled successfully!"

# Limpiar archivos objeto
clean:
	@make clean -C $(LIBFTDIR)
	@rm -rf $(OBJDIR)
	@echo "Cleaned object files"

# Limpiar todo
fclean: clean
	@make fclean -C $(LIBFTDIR)
	@rm -f $(NAME)
	@echo "Cleaned executable"

# Recompilar todo
re: fclean all

.PHONY: all clean fclean re
