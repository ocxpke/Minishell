/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:39:24 by pabmart2          #+#    #+#             */
/*   Updated: 2025/11/19 18:14:25 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "libft.h"
# include "structs.h"
/**
 * @brief Adds a new node with the given key and value to the end of the
 *        environment linked list.
 *
 * This function creates a new t_linked_env node using the provided
 * key_value array, where key_value[0] is the key and key_value[1] is the
 * value (can be NULL). The new node is appended to the end of the linked
 * list pointed to by envp.
 *
 * @param envp Pointer to the head pointer of the linked list of environment
 *             variables.
 * @param key_value Array of strings containing the key and optionally the
 *                  value. key_value[0] must be the key, key_value[1] can
 *                  be the value or NULL.
 * @return int Returns 1 on success, 0 on failure (e.g., memory allocation
 *         error).
 */
int				add_normal_node(t_linked_env **envp, char **key_value);

/**
 * @brief Adds a new piped_info node to the linked list in shell_data.
 *
 * This function allocates and initializes a new t_piped_info node with the
 * given pid, then appends it to the end of the piped_info linked list in
 * shell_data->einfo. If the list is empty, it sets the new node as the head.
 *
 * @param shell_data Pointer to the shell data structure containing the
 *                   piped_info list.
 * @param pid The process ID to store in the new node.
 * @return 1 on success (node added), 0 on failure (memory allocation error).
 */
int				add_piped_info_node(t_shell_data *shell_data, int pid);

/**
 * @brief Adds a new environment variable node to the ordered linked list.
 *
 * This function creates a new environment node from the provided key-value
 * pair and inserts it into the ordered linked list in alphabetical order
 * based on the key. If the list is empty, the new node becomes the head.
 * If the new key is lexicographically smaller than the current head's key,
 * it is inserted at the beginning. Otherwise, it delegates to
 * insert_node_ordered for proper placement.
 *
 * @param ordered_envp A double pointer to the head of the ordered
 *                     environment linked list. The list is modified in
 *                     place.
 * @param key_value A null-terminated array of strings containing the key
 *                  and value (e.g., ["KEY", "VALUE"]).
 * @return 1 on success (node added), 0 on failure (e.g., memory allocation
 *         error).
 */
int				add_ordered_node(t_linked_env **ordered_envp, char **key_value);

/**
 * @brief Checks if the given environment variable is "SHLVL" and
 *        increments its value.
 *
 * This function examines the provided key-value pair. If the key is
 * "SHLVL", it converts the value to an integer, increments it by one,
 * and updates the value with the incremented number. The previous value
 * is freed and replaced with the new one.
 *
 * @param key_value A null-terminated array of strings where
 *                  key_value[0] is the key and key_value[1] is the value.
 *                  Assumes key_value[1] is dynamically allocated.
 */
void			check_if_shelllvl(char **key_value);

/**
 * @brief Checks if the trimmed line matches the end-of-file (EOF) delimiter.
 *
 * This function compares the trimmed input line with the EOF delimiter string.
 * It returns 1 if they match based on the comparison logic, otherwise 0.
 *
 * @param trimmed_line The input line after trimming whitespace.
 * @param eof The EOF delimiter string to compare against.
 * @return 1 if the trimmed line matches the EOF, 0 otherwise.
 */
int				check_eof_match(char *trimmed_line, char *eof);

/**
 * @brief Checks if the EOF char is zero and line char is a newline.
 *
 * Used to determine if heredoc input reached a special EOF condition.
 * If 'eof' is '\0' and 'line' is '\n', returns 1 (true). If 'eof' is
 * '\0' but 'line' is not '\n', returns 0 (false). In all other cases,
 * returns 1.
 *
 * @param eof  The EOF character to check.
 * @param line The current line character to check.
 * @return int 1 if the EOF condition is met, otherwise 0.
 */
int				check_zero_eof(char eof, char line);

/**
 * @brief Clones the current environment variables into the given t_envp
 *        structure.
 *
 * Iterates through the global 'environ' array, splits each environment
 * variable into key-value pairs, checks and updates the SHLVL variable if
 * necessary, and adds each variable to both the normal and ordered
 * environment lists within the provided t_envp structure. Frees temporary
 * key-value arrays after use. Finally, updates the length of the
 * environment list and adds the PID environment variable.
 *
 * @param enviroment Pointer to the t_envp structure where the environment
 *        will be cloned.
 */
void			clone_environs(t_envp *enviroment);

/**
 * @brief Frees the entire linked list of piped information structures.
 *
 * This function iterates through the linked list starting from
 * einfo->piped_info, freeing each t_piped_info node in the list. After
 * freeing all nodes, it sets einfo->piped_info to NULL to indicate the
 * list is empty.
 *
 * @param einfo A pointer to the execution information structure
 *              containing the piped_info linked list to be freed.
 */
void			free_piped_info_list(t_einfo *einfo);

/**
 * @brief Returns the length of the longer string between two given strings.
 *
 * This function compares the lengths of two null-terminated strings and
 * returns the length of the longer one. If both strings have the same
 * length, it returns that length.
 *
 * @param str_1 A pointer to the first null-terminated string.
 * @param str_2 A pointer to the second null-terminated string.
 * @return The length of the longer string as an integer.
 */
int				ft_max_len_str(const char *str_1, const char *str_2);

/**
 * @brief Generates an array of environment variable strings for
 * execution.
 *
 * This function allocates memory for an array of strings (envp_exec)
 * based on the length of the environment list (len_env). It then
 * iterates through the linked list of environment variables (envp),
 * building a string representation for each using the
 * build_env_string function, and stores them in the array.
 *
 * @param shell_envi A pointer to the t_envp structure containing the
 *                   environment list and related data.
 * @return 1 on success, 0 if memory allocation fails, or 1 if
 *         build_env_string fails. Note: The return value is
 *         inconsistent; it returns 0 on calloc failure but 1 on
 *         build_env_string failure, which might be an error.
 */
int				generate_exec_envp(t_envp *shell_envi);

/**
 * @brief Generates a unique temporary file name for heredoc operations.
 *
 * This function creates a temporary file name starting from ".heredoc_tmp0"
 * and increments the number until it finds a name that does not exist or is
 * not writable. It uses ft_itoa to convert the number to a string and
 * ft_strjoin to concatenate it with the base name ".heredoc_tmp".
 *
 * @return A pointer to a dynamically allocated string containing the unique
 *         temporary file name, or NULL if memory allocation fails.
 */
char			*gerate_tmp_heredoc_name(void);

/**
 * @brief Splits an environment variable string into key and value.
 *
 * Given a string in the form "KEY=VALUE", this function splits it into a
 * dynamically allocated array of two strings: the key and the value.
 * If the input string does not contain '=', the entire string is treated as
 * the key, and the value is set to NULL.
 *
 * @param env The environment variable string to split.
 *            Should be in the form "KEY=VALUE" or just "KEY".
 *
 * @return A NULL-terminated array of strings [key, value], or NULL on error.
 *         The caller is responsible for freeing the returned array and its
 *         contents.
 */
char			**get_key_value(char *env);

/**
 * Retrieves the last entry in the piped_info linked list from the shell data.
 *
 * This function traverses the linked list of piped_info structures starting
 * from the head (shell_data->einfo->piped_info) and returns a pointer to the
 * last node. If the shell_data, einfo, or piped_info is NULL, it returns NULL.
 *
 * @param shell_data A pointer to the t_shell_data structure containing
 *                   execution info.
 * @return A pointer to the last t_piped_info entry, or NULL if the list is
 *         empty or invalid.
 */
t_piped_info	*get_last_pipe_info_entry(t_shell_data *shell_data);

/**
 * @brief Handles the end-of-file condition for a here-document in the
 * minishell.
 *
 * This function checks if a SIGINT signal was received. If so, it cleans up
 * by reading from an invalid file descriptor and freeing the buffer, then
 * returns NULL to indicate termination. Otherwise, it reads from an invalid
 * file descriptor, writes an error message to stderr indicating that the
 * here-document was delimited by end-of-file, and returns the buffer.
 *
 * @param buffer The buffer containing the here-document content.
 * @return NULL if SIGINT was received, otherwise the original buffer.
 */
char			*handle_heredoc_eof(char *buffer);

/**
 * @brief Appends a line and newline to the heredoc buffer.
 *
 * Concatenates the given line to the buffer, then appends a newline.
 * Handles memory freeing for temporary buffers.
 *
 * @param buffer Current heredoc buffer (may be NULL or allocated).
 * @param line   Line to append (should not be NULL).
 * @return Newly allocated buffer with the line and newline appended,
 *         or NULL on allocation failure. Caller must free the result.
 */
char			*process_heredoc_line(char *buffer, char *line);

#endif
