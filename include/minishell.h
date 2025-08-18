/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:02:38 by pablo             #+#    #+#             */
/*   Updated: 2025/08/18 14:26:41 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Cuidado con esto hay que verlo bien
# define _GNU_SOURCE

# include "../lib/libft/include/libft.h"
# include <aio.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <termios.h>

/////////////////////////////////// STRUCTS ////////////////////////////////////

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
}			t_ttype;

static char	*token_strings[] = {"ARGUMENT", "COMMAND_ROUTE", "COMMAND_BUILT_IN",
		"COMMAND_NOT_FOUND", "HEREDOC_EOF", "PIPE", "REDIRECT_IN_CHAR",
		"REDIRECT_IN_CHAR_HEREDOC", "REDIRECT_OUT_CHAR",
		"REDIRECT_OUT_CHAR_APPEND", "REDIRECT_IN_ROUTE", "REDIRECT_OUT_ROUTE",
		"UNDEFINED"};

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
	char	*string;
	t_ttype	token_type;
}			t_token;

/**
 * @struct s_line_analysis
 * @brief Structure to hold information about a parsed command line.
 *
 * This structure contains details about the number of pipes in the command,
 * the input and output file names, and whether the output is to be appended.
 *
 * @param n_pipes     Number of pipes ('|') in the command line. Initialized -1.
 * @param input_file  Pointer to the input file name for redirection.
 *                    Initialized NULL.
 * @param output_file Pointer to the output file name for redirection.
 *                    Initialized NULL.
 * @param is_append   1 if output should be appended, 0 if overwritten.
 *                    Initialized -1.
 * @param is_heredoc  1 if input is heredoc. In that case, theres a tmp file.
 *                    Initialized -1.
 */
typedef struct s_entry_info
{
	int		n_pipes;
	char	*input_file;
	char	*output_file;
	char	is_append;
	char	is_heredoc;
}			t_einfo;

typedef struct s_linked_env
{
	char *key;
	char *value;
	struct s_linked_env *next;
}			t_linked_env;

typedef struct s_envp
{
	t_linked_env *envp;
	t_linked_env *ordered_envp;
	char **envp_exec;
	int len_env;
}			t_envp;

//No me mola como ha quedado esta estrucutura
typedef struct s_shell_data
{
	t_envp shell_envi;
	char **command_exec;
	t_token **tokens;
	pid_t pid_fork;
}	t_shell_data;

//////////////////////////////////// PARSER ////////////////////////////////////

/**
 * @brief Parses the given command line string into an array of token
 *        structures.
 *
 * This function performs the following steps:
 *
 * 1. Splits the command line by pipes.
 *
 * 2. Splits each segment by quotes.
 *
 * 3. Splits each segment into arguments.
 *
 * 4. Expands environment variables in the segments.
 *
 * 5. Tokenizes the processed segments into t_token structures.
 *
 * @param command_line The input command line string to parse.
 * @return An array of pointers to t_token structures representing the parsed
 *         tokens.
 */
t_token		**parse(char *command_line);

/**
 * @brief Expands environment variables in an array of strings.
 *
 * Iterates over each string in the array `splitted`. For strings not
 * starting with a single quote ('), searches for '$' indicating an
 * environment variable. Replaces the variable with its value using
 * `expand_env`. If no variable is found, or if the string starts with
 * a single quote, calls `clean_quote` to handle quotes.
 *
 * @param splitted Array of strings to process for environment expansion.
 * @return Modified array of strings with environment variables expanded.
 */
char		**parse_expand_env(char **splitted);

/**
 * @brief Splits a command line string into an array of strings using the pipe
 *        ('|') character as a delimiter.
 *
 * This function takes an input command line string and splits it into segments
 * wherever a pipe ('|') character is found. Each segment is stored as a
 * separate string in a newly allocated matrix, suitable for further pipe
 * processing.
 *
 * @param command_line The input command line string to be split.
 * @return char** A newly allocated matrix of strings, where each string is a
 *         segment of the command line separated by pipes. Returns NULL if
 *         memory allocation fails.
 *
 * @note The caller is responsible for freeing the returned matrix.
 */
char		**split_pipes(char *command_line);

/**
 * @brief Splits each string in the array into arguments, handling quotes.
 *
 * For each element in the input array:
 * - If it does not start with a quote, split by spaces.
 * - If it starts with a quote, treat as a single argument.
 *
 * Allocates a new array of string arrays, processes each element,
 * and returns a collapsed array of arguments.
 *
 * @param array Input array of strings to split into arguments.
 * @return Newly allocated array of argument strings, or NULL on failure.
 *
 * @note The input array is freed inside this function.
 */
char		**split_args(char **array);

/**
 * @brief Splits each string in the array by quotes and processes results.
 *
 * Takes an array of strings, splits each by single/double quotes,
 * cleans substrings, and collapses results into a final array.
 * Frees the original array before returning the processed result.
 *
 * @param array Array of strings to split and process. Freed in function.
 * @return Newly allocated array of processed strings, or NULL on failure.
 */
char		**split_quotes(char **array);

/**
 * @brief Tokenizes an array of strings into an array of t_token pointers.
 *
 * This function takes an array of strings, determines its length, and parses
 * it into tokens using first_token_parse. It then classifies each token's
 * arguments using arg_classification.
 *
 * @param array The input array of strings to be tokenized.
 * @return t_token** Pointer to an array of token structures.
 */
t_token		**tokenize(char **array);

/**
 * @brief Resolves the command type for the token at index `i`.
 *
 * Checks if the token string is a built-in, a command literal, or needs
 * path resolution.
 * Sets token type to COMMAND_BUILT_IN if built-in.
 * If not built-in and cmd_literal_resolver does not return 2, returns early.
 * Otherwise, tries to resolve the command path.
 * @param tokens Array of token pointers.
 * @param i Index of the token to resolve.
 */
void		cmd_resolver(t_token **tokens, size_t i);

//////////////////////////////// PARSER - UTILS ////////////////////////////////

/**
 * @brief Collapses a 3D array of strings into a single 2D array.
 *
 * This function takes a triple pointer to a matrix of strings (`extracted`),
 * calculates the total number of strings contained in all sub-matrices,
 * and returns a new 2D array containing all strings in a single matrix.
 *
 * @param extracted A triple pointer to a 3D array of strings to be collapsed.
 * @return A double pointer to a newly allocated 2D array containing all
 *         strings.
 */
char		**collapse_extracted(char ***extracted);

/**
 * @brief Cleans a splitted string array by trimming spaces and removing empty
 * strings.
 *
 * Iterates over the input array of strings (`splitted`), trims leading and
 * trailing spaces from each string, and adds non-empty trimmed strings to a
 * new array. Empty strings (after trimming) are freed and not included in the
 * result. The resulting array is dynamically resized as needed and is
 * NULL-terminated. The original `splitted` array is freed before returning.
 *
 * @param splitted The input array of strings to be cleaned. Must be
 * NULL-terminated.
 * @return A newly allocated NULL-terminated array of cleaned strings. Returns
 * NULL if no strings remain.
 */
char		**clean_splitted(char **splitted);

/**
 * @brief Frees memory allocated for an array of t_token pointers.
 *
 * This function iterates through the array of t_token pointers, freeing the
 * memory allocated for each token's string and the token itself. Finally,
 * it frees the array of pointers.
 *
 * @param tokens Pointer to an array of t_token pointers to be freed.
 */
void		free_tokens(t_token **tokens);

void		terminal_signals(void (*func)(int));
void		block_signal(int signal, int block);

//////////////////////////////////// TOOLS /////////////////////////////////////

/**
 * @brief Creates a temporary file containing heredoc input.
 *
 * Reads input from the user until the specified EOF delimiter is encountered,
 * writes the input to a newly generated temporary file,
 * and returns the name
 * of the file. Handles memory allocation, file creation,
 * and error reporting.
 *
 * @param eof The end-of-file delimiter string for the heredoc.
 * @return On success, returns the name of the temporary file (char *).
 *         On failure, returns NULL.
 */
char		*heredoc_behaviour(char *eof);

///////////////////////////////////// UTILS ////////////////////////////////////

/**
 * @brief Extracts the first token of a specified type from a token list.
 *
 * Iterates through the linked list of tokens and returns a pointer to the
 * first token whose type matches the specified type. If no such token is
 * found, returns NULL.
 *
 * @param tokens Double pointer to the head of the token list.
 * @param type The token type to search for.
 * @return Pointer to the first token of the specified type, or NULL if not
 *         found.
 */
t_token		*extract_first_type_token(t_token **tokens, t_ttype type);

/**
 * @brief Retrieves and initializes entry information from a list of tokens.
 *
 * This function allocates and initializes a t_einfo structure, then sets its
 * input and output file fields based on the provided tokens. It also counts
 * the number of pipes present in the token list and stores this value in the
 * structure. Returns NULL if memory allocation fails.
 *
 * @param tokens Double pointer to the list of tokens to be analyzed.
 * @return Pointer to the initialized t_einfo structure, or NULL on failure.
 */
t_einfo		*get_entry_info(t_token **tokens);


// DEBUG
void		print_char_matrix(char **matrix);
void		print_token_matrix(t_token **tokens);
void		print_single_token(t_token *token, int index);

void		child_process(t_shell_data *shell_data);
void		parent_process(t_shell_data *shell_data);
char		**get_full_command(t_token **token);

char	*set_heredoc_tmp_file(char *eof);

void block_terminal_signals();
void sigint_handler(int sig);
void restore_terminal_signals();
void exit_cmd(t_shell_data *shell_data);
void cd_cmd(t_shell_data *shell_data, int *ret);
void pwd_cmd(int *ret);
void echo_cmd(t_shell_data *shell_data, int *ret);
void env_cmd(t_envp *enviroment, int *ret);
int check_if_is_built_in(t_shell_data *shell_data);

void clone_environs(t_envp *enviroment);
void init_shell_data(t_shell_data *shell_data);

int add_normal_node(t_linked_env **envp, char **key_value);
int add_ordered_node(t_linked_env **ordered_envp, char **key_value);
int generate_exec_envp(t_envp *shell_envi);
void print_envi_list(t_linked_env *envp_list, int mode);
void export_cmd(t_shell_data *shell_data, int*ret);

char **get_key_value(char *env);
void free_splitted_string(char **splitted);
void unset_cmd(t_shell_data *shell_data, int *ret);
int ft_max_len_str(char *str_1, char *str_2);

void execution_cycle(t_shell_data *shell_data);
void free_env_linked_list(t_linked_env **linked_env);
void free_shell_data(t_shell_data *shell_data);
void check_if_shelllvl(char **key_value);
int add_pid_env(t_envp *enviroment);
#endif
