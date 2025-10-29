#include "minishell.h"

#ifndef ENVIROMENT_MANAGEMENT_H
# define ENVIROMENT_MANAGEMENT_H

/**
 * @brief Adds a new environment variable node to the ordered linked list
 * in alphabetical order.
 *
 * This function creates a new node from the provided key-value pair
 * and inserts it into the ordered environment list. If the list is
 * empty, the new node becomes the head. Otherwise, it compares the
 * key with the head node's key and inserts accordingly, maintaining
 * alphabetical order.
 *
 * @param ordered_envp A pointer to the pointer of the head of the
 *                     ordered environment list. The list is modified
 *                     in place.
 * @param key_value    A null-terminated array of strings containing
 *                     the key and value (e.g., ["KEY", "VALUE"]).
 * @return             1 on success (node added), 0 on failure (e.g.,
 *                     memory allocation error).
 */
int				add_normal_node(t_linked_env **envp, char **key_value);

/**
 * @brief Adds a new environment variable node to the ordered linked
 * list.
 *
 * This function creates a new environment node from the provided
 * key-value pair and inserts it into the ordered linked list in
 * alphabetical order based on the key. If the list is empty, the new
 * node becomes the head. Otherwise, it compares the new node's key
 * with the head's key and inserts accordingly, either at the head or
 * by calling insert_node_ordered for proper placement.
 *
 * @param ordered_envp A pointer to the pointer of the head of the
 *                     ordered environment list.
 * @param key_value A null-terminated array of strings containing the
 *                  key-value pair.
 * @return 1 on success (node added), 0 on failure (e.g., memory
 *         allocation error).
 */
int				add_ordered_node(t_linked_env **ordered_envp, char **key_value);

/**
 * @brief Clones the environment variables from the global 'environ'
 * array into the provided environment structure.
 *
 * This function iterates through the system's environment variables
 * stored in the global 'environ' array. For each environment variable,
 * it extracts the key-value pair using 'get_key_value', checks if it's
 * the 'SHELLLVL' variable and handles it accordingly with
 * 'check_if_shelllvl', then edits the environment lists in the
 * 'enviroment' structure using 'edit_env_lists'. After processing all
 * variables, it frees the allocated key-value strings. Finally, it
 * calculates and sets the total length of the environment list,
 * including additional entries for PID and exit status.
 *
 * @param enviroment A pointer to the t_envp structure where the cloned
 *                   environment will be stored and managed.
 */
void			clone_environs(t_envp *enviroment);

/**
 * @brief Edits or adds environment variables in the shell's environment lists.
 *
 * This function attempts to update the value of an existing environment
 * variable specified by key_value[0] in both the unordered (envp) and
 * ordered (ordered_envp) environment lists. If the variable does not
 * exist, it adds new nodes to both lists.
 *
 * @param shell_env A pointer to the shell's environment structure
 *                  containing the envp and ordered_envp linked lists.
 * @param key_value An array of strings where key_value[0] is the variable
 *                  name and key_value[1] is the new value to set.
 * @return 0 if the variable was found and updated, 1 if a new variable
 *         was added.
 */
int				edit_env_lists(t_envp *shell_env, char **key_value);

/**
 * @brief Frees the entire linked list of environment variables.
 *
 * This function iterates through the linked list starting from the head,
 * freeing the memory allocated for each node's key, value, and the node itself.
 * After freeing all nodes, it sets the head pointer to NULL to indicate an
 * empty list.
 *
 * @param linked_env A pointer to a pointer to the head of the linked list to be
 *                   freed. The list is modified in place, and the pointer is
 *                   set to NULL upon completion.
 */
void			free_env_linked_list(t_linked_env **linked_env);

/**
 * @brief Generates an array of environment variable strings for execution.
 *
 * This function allocates memory for an array of strings representing the
 * environment variables from the shell's environment list. It iterates through
 * the linked list of environment variables, building a string for each one
 * using the build_env_string function, and stores them in the envp_exec array.
 * The array is null-terminated.
 *
 * @param shell_envi A pointer to the t_envp structure containing the shell's
 *                   environment variables and related data.
 *
 * @return 1 on success, 0 or 1 on failure (with error message printed for
 *         allocation failure).
 *
 * @note If memory allocation fails for envp_exec or any individual string,
 *       the function returns early with an error indication.
 */
int				generate_exec_envp(t_envp *shell_envi);

/**
 * @brief Searches for an environment variable node in a linked list by key.
 *
 * This function iterates through the linked list of environment variables
 * starting from the provided linked_env pointer. It compares the key of each
 * node with the given key using a custom string comparison that considers
 * the maximum length of the two strings. If a match is found, the function
 * returns a pointer to that node. If no match is found or if either key or
 * linked_env is NULL, it returns NULL.
 *
 * @param key The key to search for in the environment list. Must not be NULL.
 * @param linked_env The head of the linked list of environment variables.
 *                   Must not be NULL.
 * @return A pointer to the environment node with the matching key, or NULL
 *         if not found or if inputs are invalid.
 */
t_linked_env	*get_enviroment_node(const char *key, t_linked_env *linked_env);

/**
 * @brief Retrieves the value of an environment variable from a linked list.
 *
 * This function searches through a linked list of environment variables
 * to find the one matching the provided key. It compares the keys using
 * a custom string comparison function up to the maximum length of the
 * shorter string.
 *
 * @param key The key of the environment variable to search for.
 * @param linked_env A pointer to the head of the linked list of
 * environment variables.
 * @return The value associated with the key if found, or NULL if not
 * found or if inputs are invalid.
 */
char			*get_enviroment_value(const char *key,
					t_linked_env *linked_env);

/**
 * @brief Constructs an environment variable string in the format
 * "PID=<numeric_part>".
 *
 * This function takes a string representing a process ID, skips any
 * leading non-digit characters, extracts the numeric part, and
 * prepends "PID=" to create a valid environment variable string. The
 * result is dynamically allocated and must be freed by the caller.
 *
 * @param pid A null-terminated string containing the process ID,
 *            potentially with leading non-digit characters
 *            (e.g., "pid123" -> "PID=123").
 * @return A dynamically allocated string in the format "PID=<digits>",
 *         or NULL if memory allocation fails or if the substring
 *         extraction fails.
 */
char			*get_pid_env(char *pid);

/**
 * @brief Retrieves the process ID (PID) from the /proc/self/status file.
 *
 * This function opens the /proc/self/status file, reads it line by line using
 * ft_get_next_line, and searches for the line starting with "Pid:". Once found,
 * it returns a dynamically allocated string containing that line. If the file
 * cannot be opened or the "Pid:" line is not found, it returns NULL.
 *
 * @return A pointer to a null-terminated string containing the "Pid:" line,
 *         or NULL if an error occurs or the line is not found. The caller is
 *         responsible for freeing the returned string.
 */
char			*get_pid_from_file(void);

/**
 * @brief Modifies the value of an environment variable in both the normal
 * and ordered environment lists.
 *
 * This function searches for the environment variable specified by the key
 * in both the normal environment list (shell_env->envp) and the ordered
 * environment list (shell_env->ordered_envp). If found, it frees the
 * existing values and assigns a duplicate of the new value to both nodes.
 *
 * @param shell_env A pointer to the t_envp structure containing the
 *                  environment lists.
 * @param key The key of the environment variable to modify (const char *).
 * @param new_key The new value to assign to the environment variable
 *                (char *).
 * @return 1 if the modification was successful, 0 otherwise (e.g., if key
 *         not found or invalid inputs).
 *
 * @note The function assumes that the key exists in both lists; if not, it
 * returns 0 without modification.
 * @note Memory is managed internally: old values are freed, and new_key is
 * duplicated using ft_strdup.
 */
int				modify_value_env_node(t_envp *shell_env, const char *key,
					char *new_key);

#endif
