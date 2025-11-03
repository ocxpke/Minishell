#include "minishell.h"

#ifndef ENVIROMENT_MANAGEMENT_H
#define ENVIROMENT_MANAGEMENT_H

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
int add_normal_node(t_linked_env **envp, char **key_value);

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
int add_ordered_node(t_linked_env **ordered_envp, char **key_value);

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
void clone_environs(t_envp *enviroment);

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
int edit_env_lists(t_envp *shell_env, char **key_value);

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
void free_env_linked_list(t_linked_env **linked_env);

int modify_value_env_node(t_envp *shell_env, const char *key, char *new_key);
int modify_exit_status_value(t_envp *shell_envp, int new_exit_status);

char	*get_enviroment_value(const char *key, t_linked_env *linked_env);
t_linked_env	*get_enviroment_node(const char *key, t_linked_env *linked_env);
char	*get_pid_from_file(void);
char	*get_pid_env(char *pid);
void	check_if_shelllvl(char **key_value);

#endif
