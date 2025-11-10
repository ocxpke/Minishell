/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:46:49 by pablo             #+#    #+#             */
/*   Updated: 2025/11/10 20:51:56 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stddef.h>
# include <sys/types.h>

/**
 * @enum e_token_type
 * @brief Represents the different types of tokens used in the minishell parser.
 *
 * The token types are used to classify parsed elements in the shell input.
 *
 * - ARGUMENT: A command argument.
 *
 * - COMMAND_ROUTE: An external command path.
 *
 * - COMMAND_BUILT_IN: A built-in shell command.
 *
 * - HEREDOC_EOF: End-of-file marker for heredoc.
 *
 * - PIPE: Pipe operator '|'.
 *
 * - REDIRECT_IN_CHAR: Input redirection character '<'.
 *
 * - REDIRECT_IN_CHAR_HEREDOC: Input redirection for heredoc '<<'.
 *
 * - REDIRECT_OUT_CHAR: Output redirection character '>'.
 *
 * - REDIRECT_OUT_CHAR_APPEND: Output redirection with append '>>'.
 *
 * - REDIRECT_IN_ROUTE: Input redirection to a file.
 *
 * - REDIRECT_OUT_ROUTE: Output redirection to a file.
 *
 * - UNDEFINED: Undefined or unrecognized token type.
 */
typedef enum e_token_type
{
	ARGUMENT,
	COMMAND_ROUTE,
	COMMAND_BUILT_IN,
	COMMAND_NOT_FOUND,
	HEREDOC_EOF,
	PIPE,
	REDIRECT_IN_CHAR,
	REDIRECT_IN_CHAR_HEREDOC,
	REDIRECT_OUT_CHAR,
	REDIRECT_OUT_CHAR_APPEND,
	REDIRECT_IN_ROUTE,
	REDIRECT_OUT_ROUTE,
	UNDEFINED
}						t_ttype;

/**
 * @struct s_token
 * @brief Represents a token in the minishell parser.
 *
 * This structure holds information about a parsed token, including
 * its string representation and its type.
 *
 * @param s_token::string
 *   The string value of the token.
 * @param s_token::t_ttype
 *   The type of the token, represented by the t_ttype enum.
 */
typedef struct s_token
{
	char				*string;
	t_ttype				token_type;
}						t_token;

/**
 * @brief Structure representing information about a piped command in a shell.
 *
 * This structure is used to store details about each command in a pipeline,
 * including the process ID, the command name or file, and a pointer to the next
 * command in the pipeline.
 *
 * @param pid The process ID of the command.
 * @param file_cmmd_name A pointer to a string containing the name of the
 *                       command or file being executed.
 * @param next A pointer to the next element in the linked list of piped
 *             commands.
 */
typedef struct s_piped_info
{
	int					pid;
	char				*file_cmmd_name;
	struct s_piped_info	*next;
}						t_piped_info;

/**
 * @brief Structure holding information about a command, including
 *        redirection details and arguments.
 *
 * This structure encapsulates the necessary data for executing a
 * command in a shell environment, such as input/output redirections,
 * heredoc flags, and the command with its arguments.
 *
 *
 * @param input_file Path to the file from which input should be read
 *                   (for input redirection, e.g., <). NULL if no input
 *                   redirection is specified.
 * @param output_file Path to the file to which output should be
 *                    written (for output redirection, e.g., > or >>).
 *                    NULL if no output redirection is specified.
 * @param is_append Flag indicating if output redirection should
 *                  append to the file (1 for >>, 0 for >).
 * @param is_heredoc Flag indicating if heredoc redirection is used
 *                   (1 for <<, 0 otherwise).
 * @param array_size Number of elements in the cmd_and_args array
 *                   (including the command and all arguments).
 * @param cmd_and_args Null-terminated array of strings representing
 *                     the command and its arguments. The first
 *                     element is the command, followed by arguments.
 *                     NULL-terminated.
 */
typedef struct s_command_info
{
	char				*input_file;
	char				*output_file;
	char				is_append;
	char				is_heredoc;
	size_t				array_size;
	char				**cmd_and_args;
}						t_cinfo;

/**
 * @struct s_entry_info
 * @brief Structure to hold parsed command line info for minishell.
 *
 * Stores details about the parsed command line, including:
 *
 * - Number of pipes ('|') present.
 *
 * - Input/output file names for redirection.
 *
 * - Output append mode and heredoc usage.
 *
 * - Parsed commands as a triple pointer to strings.
 *
 * Members:
 * @param n_pipes     Number of pipes ('|') in the command line.
 *                    Initialized to -1.
 * @param input_file  Pointer to input file name for redirection.
 *                    Initialized to NULL.
 * @param output_file Pointer to output file name for redirection.
 *                    Initialized to NULL.
 * @param is_append   1 if output should be appended, 0 if overwritten.
 *                    Initialized to -1.
 * @param is_heredoc  1 if input uses heredoc (temporary file created),
 *                    0 otherwise. Initialized to -1.
 * @param commands    Triple pointer to parsed commands and their arguments.
 */
typedef struct s_entry_info
{
	int					n_pipes;
	t_cinfo				**cinfos;
	t_piped_info		*piped_info;
}						t_einfo;

/**
 * @brief Structure representing a node in a linked list for environment
 * variables.
 *
 * This structure is used to store key-value pairs for environment variables
 * in a linked list format. Each node contains a key (variable name), its
 * corresponding value, and a pointer to the next node in the list.
 *
 *
 * @param key The name of the environment variable (e.g., "PATH").
 * @param value The value associated with the environment variable
 *              (e.g., "/usr/bin:/bin").
 * @param next Pointer to the next node in the linked list, or NULL if this is
 *             the last node.
 */
typedef struct s_linked_env
{
	char				*key;
	char				*value;
	struct s_linked_env	*next;
}						t_linked_env;

/**
 * @brief Structure representing the environment variables for the
 * minishell.
 *
 * This structure holds the environment variables in multiple forms: as a
 * linked list, an ordered linked list, and as an array suitable for
 * execution. It also tracks the length of the environment variables.
 *
 * @param envp Pointer to the head of the linked list of environment
 *             variables.
 * @param ordered_envp Pointer to the head of the ordered (sorted) linked
 *                     list of environment variables.
 * @param envp_exec Array of strings representing the environment
 *                  variables, formatted for use with execve.
 * @param len_env Integer representing the number of environment
 *                variables in the list.
 */
typedef struct s_envp
{
	t_linked_env		*envp;
	t_linked_env		*ordered_envp;
	char				**envp_exec;
	int					len_env;
}						t_envp;

/**
 * @struct s_shell_data
 * @brief Structure representing the core data for the minishell program.
 *
 * This structure encapsulates essential components of the shell's state,
 * including environment variables, tokenized input, process ID for forked
 * processes, and error information.
 *
 * @typedef t_shell_data
 * @brief Alias for the s_shell_data structure.
 *
 * @param shell_envi Holds the shell's environment variables.
 * @param tokens Array of pointers to tokenized input elements.
 * @param pid_fork Process ID of the forked child process.
 * @param einfo Pointer to error information structure.
 */
typedef struct s_shell_data
{
	t_envp				shell_envi;
	t_token				**tokens;
	pid_t				pid_fork;
	t_einfo				*einfo;
	char				*prompt;
}						t_shell_data;

#endif
