/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:02:38 by pablo             #+#    #+#             */
/*   Updated: 2025/11/03 21:52:49 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

// Cuidado con esto hay que verlo bien
# define _GNU_SOURCE

# include "../lib/libft/include/libft.h"
# include "./structs.h"
# include "./built_in.h"
# include "./enviroment_management.h"
# include "./process_management.h"
# include "./shell_data.h"
# include "./signals.h"
# include "./tools.h"
# include "parser.h"
# include <aio.h>
# include <fcntl.h>

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>


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
char	*heredoc_behaviour(char *eof);

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
char	*get_shell_prompt(t_linked_env *envs);

/**
 * @brief Frees all memory associated with a t_einfo structure.
 *
 * Releases memory for input/output file strings, the commands array
 * (including each command), and the t_einfo structure itself.
 * Safely handles NULL pointers to prevent segmentation faults.
 *
 * @param einfo Double pointer to the t_einfo structure to be freed.
 */
void clean_entry_info(t_einfo **einfo);

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
t_token	*extract_first_type_token(t_token **tokens, t_ttype type);

/**
 * @brief Finds the first pipe token that is not at the beginning of the
 * token array.
 *
 * This function skips pipe tokens that appear at the start of the array
 * (which are typically separators from previous commands in a pipeline)
 * and returns the first pipe token that appears after the initial tokens.
 *
 * @param tokens Pointer to the token array to search in.
 * @return Pointer to the first pipe token that is not at the beginning,
 * or NULL if none found.
 */
t_token	*find_next_pipe_after_command(t_token **tokens);

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
t_einfo	*get_entry_info(t_token **tokens);

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
 * @note TODO: Consider making count_tokens variadic for better flexibility.
 */
int		set_cinfos(t_token **tokens, t_einfo *einfo);

/**
 * @brief Set command input file from tokens.
 *
 * Scans tokens for input redirections: '<' or '<<'.
 * For '<', sets cinfo->input_file to the route token's string and is_heredoc
 * to 0.
 * For '<<', resets GNL state, calls heredoc_behaviour(), sets input_file to
 * the returned path, and is_heredoc to 1.
 * If no redirection, leaves cinfo unchanged.
 * Redirections are only considered if they appear before the specified pipe
 * token.
 *
 * @param tokens Pointer to token list head.
 * @param cinfo Command info structure to update.
 * @param pipe A pointer to the pipe token that limits the scope of the
 *             redirection search. Redirections after this pipe are ignored.
 *             Pass NULL to search the entire token list.
 *
 * @note Ownership: input_file points to token's string or heap-allocated path
 *       from heredoc_behaviour(); caller must free if from heredoc.
 */
int		set_command_input_file(t_token **tokens, t_cinfo *cinfo, t_token *pipe);

/**
 * @brief Sets the output file for a command based on redirection tokens.
 *
 * This function processes redirection tokens from the token list to determine
 * the output file for the command. It handles both standard output redirection
 * ('>') and append redirection ('>>'). If a redirection token is found, it
 * extracts the subsequent file name token and stores it in the command info
 * structure. The function also sets a flag indicating whether the output
 * should be appended or overwritten. Redirections are only considered if they
 * appear before the specified pipe token.
 *
 * @param tokens A pointer to the pointer of the token list. The list may be
 *               modified as tokens are extracted.
 * @param cinfo  A pointer to the command info structure where the output file
 *               and append flag will be set.
 * @param pipe   A pointer to the pipe token that limits the scope of the
 *               redirection search. Redirections after this pipe are ignored.
 *               Pass NULL to search the entire token list.
 * @return       0 on success, or 1 if memory allocation fails during string
 *               duplication.
 */
int		set_command_output_file(t_token **tokens, t_cinfo *cinfo, t_token *pipe);

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
