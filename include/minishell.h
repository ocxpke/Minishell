/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:02:38 by pablo             #+#    #+#             */
/*   Updated: 2025/11/30 12:51:09 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include "built_in.h"
# include "enviroment_management.h"
# include "libft.h"
# include "parser.h"
# include "process_management.h"
# include "shell_data.h"
# include "signals.h"
# include "structs.h"
# include "tools.h"
# include <aio.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

//////////////////////////////////// TOOLS /////////////////////////////////////

/**
 * @brief Handles the behavior for heredoc input in the shell.
 *
 * This function sets up signal handling for heredoc, reads input until the
 * specified end-of-file (EOF) delimiter is encountered, generates a temporary
 * file name, writes the collected input to that file, and returns the file
 * name via the result parameter. It manages interruptions and errors during
 * the process.
 *
 * @param eof A null-terminated string representing the EOF delimiter for the
 *            heredoc input.
 * @param result A pointer to a char pointer where the generated temporary file
 *               name will be stored upon success. The caller is responsible
 *               for freeing this memory.
 *
 * @return HEREDOC_SUCCESS on successful completion,
 *         HEREDOC_INTERRUPTED if interrupted by SIGINT,
 *         HEREDOC_ERROR on other failures (e.g., memory allocation or file
 *         operations).
 */
int		heredoc_behaviour(char *eof, char **result);

/**
 * @brief Counts the number of tokens of a specific type in a token array.
 *
 * Iterates through the given array of token pointers and counts how many
 * tokens have a token_type matching the specified type.
 *
 * @param tokens Array of pointers to t_token structures, terminated by NULL.
 * @param type The token type to count (of type t_ttype).
 * @return The number of tokens in the array that match the specified type.
 */
int		count_tokens(t_token **tokens, t_ttype type);

/**
 * @brief Parses a list of tokens and constructs a 3D array of
 * command arguments.
 *
 * Counts the number of command tokens (built-in and routed), allocates a
 * 3D array to store arguments for each command, and fills it using
 * set_commands_loop. The resulting array is NULL-terminated.
 *
 * @param tokens: Pointer to an array of token pointers representing the parsed
 * input.
 *
 * @return: Pointer to the 3D array of command arguments, or NULL on
 * allocation failure.
 */
char	***get_commands(t_token **tokens);

///////////////////////////////////// UTILS ////////////////////////////////////

/**
 * @brief Generates the shell prompt string, incorporating color and
 * current working directory.
 *
 * This function constructs a complete shell prompt by first creating a
 * colored base prompt, retrieving the current directory, combining them,
 * and finalizing the prompt string. It handles memory allocation and
 * deallocation appropriately, returning NULL on failure.
 *
 * @param envs A pointer to the linked list of environment variables used
 * for prompt customization.
 * @return A dynamically allocated string representing the final shell
 * prompt, or NULL if any step fails.
 */
char	*get_prompt(t_linked_env *envs);

/**
 * @brief Frees all memory associated with a t_einfo structure.
 *
 * Releases memory for input/output file strings, the commands array
 * (including each command), and the t_einfo structure itself.
 * Safely handles NULL pointers to prevent segmentation faults.
 *
 * @param einfo Double pointer to the t_einfo structure to be freed.
 */
void	clean_entry_info(t_einfo **einfo);

/**
 * @brief Extracts the position of the first token of a specified type.
 *
 * Scans the NULL-terminated array of tokens and returns the pointer to the
 * array slot that stores the first token whose type matches @p type. The
 * original array is not modified.
 *
 * @param tokens Double pointer to the head of the token list.
 * @param type Token type to search for.
 * @return Pointer to the array entry pointing at the matching token, or NULL
 *         if no match exists.
 */
t_token	**extract_first_type_token(t_token **tokens, t_ttype type);

/**
 * @brief Finds the first pipe token that is not at the beginning of the
 * token array.
 *
 * This function skips pipe tokens that appear at the start of the array
 * (which are typically separators from previous commands in a pipeline)
 * and returns the first pipe token that appears after the initial tokens.
 *
 * @param tokens Pointer to the token array to search in.
 * @return Pointer to the position in the array of the first pipe token
 * that is not at the beginning, or NULL if none found.
 */
t_token	**find_next_pipe_pos_after_command(t_token **tokens);

/**
 * @brief Initializes entry information for the shell command parsing.
 *
 * This function processes the tokens to set command information, counts
 * the number of pipes in the token list, initializes piped_info to NULL,
 * and frees the tokens.
 *
 * @param tokens A pointer to the pointer of the token list to process and
 * free.
 * @param einfo A pointer to the entry info structure to populate.
 * @return 0 on success, or the return value of set_cinfos on failure.
 */
int		get_entry_info(t_token **tokens, t_einfo *einfo);

/**
 * Retrieves the value for a key from a linked environment list.
 *
 * @param key        The key to search for.
 * @param linked_env Pointer to the head of the list.
 * @return           The value for the key if found, else NULL.
 *
 * Iterates through the list and compares each node's key with the given key.
 * If both length and content match, returns the value. Else, returns NULL.
 */
char	*get_linked_env(const char *key, t_linked_env *linked_env);

/**
 * @brief Allocates and initializes a new t_einfo structure.
 *
 * This function allocates memory for a t_einfo structure and initializes
 * its members to default values:
 *
 *   - input_file, output_file and commands are set to NULL.
 *
 *   - is_append, is_heredoc, and n_pipes are set to -1.
 *
 * @return Pointer to the newly allocated and initialized t_einfo structure,
 *         or NULL if memory allocation fails.
 */
t_einfo	*initialize_einfo(void);

//////////////////////////////// UTILS - CINFO /////////////////////////////////
/**
 * @brief Counts the number of argument tokens following a command token.
 *
 * @param tokens   Array of pointers to t_token structures.
 * @param cmd_pos  Index of the command token in the array.
 * @return         Number of consecutive argument tokens after the command.
 */
int		count_command_args(t_token **tokens, int cmd_pos);

/**
 * @brief Retrieve the n-th command token from a NULL-terminated token array.
 *
 * Scans the provided NULL-terminated array of t_token pointers and counts
 * only tokens whose token_type is one of:
 *
 *   - COMMAND_BUILT_IN
 *
 *   - COMMAND_ROUTE
 *
 *   - COMMAND_NOT_FOUND
 *
 * The index n is zero-based (n == 0 returns the first matching command
 * token). Scanning stops at the first NULL entry in the array.
 *
 * @param tokens NULL-terminated array of pointers to t_token to search.
 * @param n      Zero-based index of the command token to retrieve.
 * @param token_pos Optional output pointer. If non-NULL, receives the index
 *                  within the tokens array of the returned token. If no
 *                  matching token is found, *token_pos is set to -1.
 *
 * @return Pointer to the n-th matching t_token on success, or NULL if fewer
 *         than n+1 matching command tokens exist. If NULL is returned and
 *         token_pos is non-NULL, *token_pos is set to -1.
 */
t_token	*get_next_command(t_token **tokens, int n, int *token_pos);

/**
 * @brief Cleans up an array of command info structures by freeing
 * allocated memory.
 *
 * This function iterates through the array of t_cinfo pointers, freeing
 * the memory associated with each structure's members (args, command,
 * input_file, output_file) and then the structure itself. Finally, it
 * frees the array of pointers.
 *
 * @param cinfos A pointer to an array of t_cinfo pointers, terminated by
 * a NULL pointer. The array and its contents will be deallocated.
 */
void	clean_cinfos(t_cinfo **cinfos);

/**
 * @brief Finds the start position of the pipeline containing the given command.
 *
 * Searches backwards from token_pos to find the previous PIPE token or the
 * beginning of the token array. Returns the position right after the pipe
 * (start of current pipeline) or 0 if no pipe is found.
 *
 * @param tokens Array of token pointers.
 * @param token_pos Position of the command token.
 * @return Position of the start of the current pipeline.
 */
int		find_pipeline_start(t_token **tokens, int token_pos);

/**
 * @brief Sets up command information structures in the execution info.
 *
 * This function calculates the number of commands by counting tokens of types
 * COMMAND_BUILT_IN, COMMAND_NOT_FOUND, and COMMAND_ROUTE. It then allocates
 * memory for an array of command info pointers in the execution info structure
 * and populates it by calling set_cinfos_loop.
 *
 * @param tokens A pointer to an array of tokens representing the command line.
 * @param einfo A pointer to the execution info structure where command infos
 *              will be stored.
 * @return 0 on success, 1 on memory allocation failure.
 *
 */
int		set_cinfos(t_token **tokens, t_einfo *einfo);

/**
 * @brief Sets the input file for a command based on redirection tokens.
 *
 * This function extracts the first REDIRECT_IN_ROUTE token and the first
 * REDIRECT_IN_CHAR_HEREDOC token from the token list. It prioritizes the route
 * redirection if it appears before any pipe or heredoc token. If a route is
 * found and meets the conditions, it sets the input file in cinfo and marks
 * it as not a heredoc. Otherwise, it delegates to set_heredoc_input_file.
 *
 * @param tokens Pointer to the token list to process.
 * @param cinfo Pointer to the command info structure to update.
 * @param pipe Pointer to the pipe token for comparison (can be NULL).
 * @return 0 on success, 1 on memory allocation failure.
 */
int		set_command_input_file(t_token **tokens, t_cinfo *cinfo,
			t_token **pipe);

/**
 * @brief Sets the output file for a command based on redirection tokens.
 *
 * Processes ">" (overwrite) and ">>" (append) operators in the token list
 * to set the command's output file. Prioritizes the first valid redirection
 * before any pipe token, updating the command info with the output route
 * and append flag.
 *
 * @param tokens Pointer to the token list to search for redirection
 *               operators.
 * @param cinfo Pointer to the command info structure where output file
 *              route and append flag are set.
 * @param pipe Pointer to the pipe token limiting redirection scope
 *             (ignores redirections after the pipe).
 * @return 0 on success or when no valid redirection is found.
 */
int		set_command_output_file(t_token **tokens, t_cinfo *cinfo,
			t_token **pipe);

// DEBUG
void	debug_shell_info(t_shell_data *shell_data);
void	print_char_matrix(char **matrix);
void	print_token_matrix(t_token **tokens);
void	print_single_token(t_token *token, int index);

char	**get_full_command(t_token **token);

// char *set_heredoc_tmp_file(char *eof);???

char	*generate_cmmd_file_name(int index);
int		generate_cmmd_file(char *file_name, char *cmmd_to_write);

#endif
