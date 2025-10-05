/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:39:24 by pabmart2          #+#    #+#             */
/*   Updated: 2025/09/27 21:13:33 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tools.h
 * @brief Utility functions and structures for minishell environment and
 *        process management.
 *
 * This header provides declarations for functions and structures used to
 * manipulate environment variables, manage linked lists, handle shell
 * level, and manage piped process information within the minishell
 * project.
 */

#include "minishell.h"

#ifndef TOOLS_H
# define TOOLS_H

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
int				add_ordered_node(t_linked_env **ordered_envp, char **key_value);
int				generate_exec_envp(t_envp *shell_envi);

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

void			free_splitted_string(char **splitted);
int	ft_max_len_str(const char *str_1, const char *str_2);

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

int				add_piped_info_node(t_shell_data *shell_data, int pid);
void			free_piped_info_list(t_einfo *einfo);
t_piped_info	*get_last_pipe_info_entry(t_shell_data *shell_data);

#endif
