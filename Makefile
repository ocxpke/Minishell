# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:34:30 by pabmart2          #+#    #+#              #
#    Updated: 2025/08/01 13:57:30 by pabmart2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline
DEBUG_FLAGS = -g -fno-inline -gdwarf-4
ASAN_FLAGS = $(DEBUG_FLAGS) -fsanitize=address -O1
TSAN_FLAGS = $(DEBUG_FLAGS) -fsanitize=thread -O1

BUILD_DIR = build

OBJ_DIR = build/obj

NAME = minishell

HEADERS = \
	include/minishell.h \
	include/colors.h \

SRC = \
	src/main.c \
	src/parse/parser_cmd_resolver.c \
	src/parse/parser_env.c \
	src/parse/parser_split_args.c \
	src/parse/parser_split_pipes.c \
	src/parse/parser_split_quotes.c \
	src/parse/parser_tokenization.c \
	src/parse/parser.c \
	src/parse/utils/parser_clean_splitted.c \
	src/parse/utils/parser_collapse.c \
	src/parse/utils/parser_free_tokens.c \
	src/signals/signals.c

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

SIGNALS_SRCS = $(SRCDIR)/signals/signals.c \
				$(SRCDIR)/signals/sig_handlers.c

PROCESS_SRCS = $(SRCDIR)/process_management/child_process.c \
				$(SRCDIR)/process_management/parent_process.c

BUILT_IN_SRCS = $(SRCDIR)/built_in/built_in_cmds.c \
				$(SRCDIR)/built_in/manage_built_in.c


OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LIBS = \
	lib/libft/include/libft.a

INCLUDES = \
	-Iinclude \
	-Ilib/libft/include \

all: $(NAME)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(NAME)

debug-asan: CFLAGS += $(ASAN_FLAGS)
debug-asan: clean $(NAME)

debug-tsan: CFLAGS += $(TSAN_FLAGS)
debug-tsan: clean $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[31mObject files removed\033[0m"

fclean: clean
	@rm -f $(BUILD_DIR)/$(NAME)
	@echo "\033[31m$(NAME) removed\033[0m"

re: fclean
	$(MAKE) all

libft:
	@echo "\033[33mCompiling libft...\033[0m"
	@$(MAKE) -C lib/libft

$(NAME): libft $(OBJ)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(OBJ) -o $(BUILD_DIR)/$(NAME) $(LIBS) $(INCLUDES)
	@echo "\033[32m\n¡$(NAME) compiled! \
	ᕦ(\033[36m⌐■\033[32m_\033[36m■\033[32m)ᕤ\n"

$(OBJ) : $(OBJ_DIR)/%.o : %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[34mCompiling: \033[0m$<"

################################################
.PHONY: all debug debug-asan debug-tsan clean fclean re
