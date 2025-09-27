/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:01:36 by jose-ara          #+#    #+#             */
/*   Updated: 2025/09/27 19:02:10 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_in_env_list(t_linked_env **env_list, char *key)
{
	t_linked_env	*aux;
	t_linked_env	*prev_aux;
	int				loop;

	loop = 1;
	aux = *env_list;
	while (aux && loop)
	{
		if (!ft_strncmp(aux->key, key, ft_max_len_str(aux->key, key)))
			loop = 0;
		else
		{
			prev_aux = aux;
			aux = aux->next;
		}
	}
	if (!aux)
		return (0);
	if (!prev_aux)
		*env_list = aux->next;
	else
		prev_aux->next = aux->next;
	return (free(aux->key), free(aux->value), free(aux), 1);
}

void	unset_cmd(t_shell_data *shell_data, int *ret)
{
	int	i;

	i = 0;
	*ret = 1;
	while (shell_data->tokens[i])
	{
		if (shell_data->tokens[i]->string)
		{
			/** Aqui en el if nos vale && y
				|| pues si no lo encuntra en uno no debria de buscar en el otro
				*  pongo && por eficiencia
				*/
			if (search_in_env_list(&(shell_data->shell_envi.envp),
					shell_data->tokens[i]->string)
				&& search_in_env_list(&(shell_data->shell_envi.ordered_envp),
					shell_data->tokens[i]->string))
				shell_data->shell_envi.len_env--;
		}
		i++;
	}
}
