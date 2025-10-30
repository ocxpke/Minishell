/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_piped_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:03:31 by jose-ara          #+#    #+#             */
/*   Updated: 2025/10/30 10:48:36 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_piped_info_node(t_shell_data *shell_data, int pid)
{
	t_piped_info	*new_node;
	t_piped_info	*aux;

	new_node = (t_piped_info *)ft_calloc(1, sizeof(t_piped_info));
	if (!new_node)
		return (0);
	new_node->pid = pid;
	new_node->next = NULL;
	if (!shell_data->einfo->piped_info)
		return (shell_data->einfo->piped_info = new_node, 1);
	aux = shell_data->einfo->piped_info;
	while (aux->next)
		aux = aux->next;
	aux->next = new_node;
	return (1);
}

void	free_piped_info_list(t_einfo *einfo)
{
	t_piped_info	*to_free;
	t_piped_info	*aux;

	aux = einfo->piped_info;
	while (aux)
	{
		to_free = aux;
		aux = aux->next;
		free(to_free);
	}
	einfo->piped_info = NULL;
}

t_piped_info	*get_last_pipe_info_entry(t_shell_data *shell_data)
{
	t_piped_info	*aux;

	if (!shell_data->einfo || !shell_data->einfo->piped_info)
		return (NULL);
	aux = shell_data->einfo->piped_info;
	while (aux->next)
		aux = aux->next;
	return (aux);
}
