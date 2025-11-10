/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:39:04 by pabmart2          #+#    #+#             */
/*   Updated: 2025/11/10 20:51:55 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_DATA_H
# define SHELL_DATA_H
# include "structs.h"

/**
 * @brief Frees all dynamically allocated memory associated with the
 * shell_data structure.
 *
 * This function releases memory for the shell environment variables
 * (both as a split string and as linked lists) and cleans up the entry
 * information structure. It should be called when the shell_data is no
 * longer needed to prevent memory leaks.
 *
 * @param shell_data Pointer to the t_shell_data structure to be freed.
 */
void	free_shell_data(t_shell_data *shell_data);

/**
 * @brief Initializes the t_shell_data structure with default values.
 *
 * This function sets all members of the provided t_shell_data pointer to their
 * initial states, including setting pointers to NULL and counters to zero.
 * It also calls clone_environs to initialize the shell environment variables.
 *
 * @param shell_data Pointer to the t_shell_data structure to initialize.
 */
void	init_shell_data(t_shell_data *shell_data);

#endif
