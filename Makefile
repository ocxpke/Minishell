# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pablo <pablo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:34:30 by pabmart2          #+#    #+#              #
#    Updated: 2025/08/18 14:53:30 by pablo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
# TODO: Incluir -Werror cuando acabemos de depurar
CFLAGS = -Wall -Wextra
DEBUG_FLAGS = -g -fno-inline -gdwarf-4
ASAN_FLAGS = $(DEBUG_FLAGS) -fsanitize=address -O1
LDFLAGS = -lreadline

BUILD_DIR = build

OBJ_DIR = build/obj

NAME = minishell

HEADERS = \
	include/minishell.h \
	include/colors.h \

SRC = src/main.c $(SHELL_DATA_SRC) $(PROC_MNG_SRC) $(SIGNALS_SRC) $(PARSER_SRC) \
	$(TOOLS_SRC) $(BUILT_IN_SRC) $(UTILS_SRC)

BUILT_IN_SRC = src/built_in/manage_built_in.c \
				src/built_in/echo_command.c \
				src/built_in/cd_command.c \
				src/built_in/pwd_command.c \
				src/built_in/export_command.c \
				src/built_in/unset_command.c \
				src/built_in/env_command.c \
				src/built_in/exit_command.c

PARSER_SRC = src/parser/parser_cmd_resolver.c \
			src/parser/parser_env.c \
			src/parser/parser_split_args.c \
			src/parser/parser_split_pipes.c \
			src/parser/parser_split_quotes.c \
			src/parser/parser_tokenization.c \
			src/parser/parser.c \
			src/parser/utils/parser_clean_splitted.c \
			src/parser/utils/parser_collapse.c \
			src/parser/utils/parser_free_tokens.c

PROC_MNG_SRC = src/process_management/child_process.c \
				src/process_management/parent_process.c \
				src/process_management/manage_execution.c

SHELL_DATA_SRC = src/shell_data/manage_shell_data.c

SIGNALS_SRC = src/signals/signals.c \
				src/signals/sig_handlers.c


TOOLS_SRC = src/tools/tools_heredoc.c \
			src/tools/tools_enviroment.c \
			src/tools/tools_envp_linked_list.c \
			src/tools/tools_aux_envp_linked_list.c \
			src/tools/tools_modify_env.c

UTILS_SRC = src/utils/utils_extract_tokens.c \
			src/utils/utils_get_entry_info.c \


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

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C lib/libft
	@echo -e "\033[31mObject files removed\033[0m"

fclean: clean
	@rm -f $(BUILD_DIR)/$(NAME)
	@make fclean -C lib/libft
	@echo -e "\033[31m$(NAME) removed\033[0m"

re: fclean
	$(MAKE) all

libft:
	@echo -e "\033[33mCompiling libft...\033[0m"
	@$(MAKE) -C lib/libft

$(NAME): libft $(OBJ)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(OBJ) -o $(BUILD_DIR)/$(NAME) $(LIBS) $(INCLUDES) $(LDFLAGS)
	@echo -e "\033[32m\n¡$(NAME) compiled! \
	ᕦ(\033[36m⌐■\033[32m_\033[36m■\033[32m)ᕤ\033[0m\n"

$(OBJ) : $(OBJ_DIR)/%.o : %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo -e "\033[34mCompiling: \033[0m$<"

################################################
.PHONY: all debug debug-asan clean fclean re
