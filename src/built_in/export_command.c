/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:00:57 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/12 21:28:51 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_cmd(t_shell_data *shell_data, t_cinfo *cinfo, int *ret)
{
	char	**key_value;
	int		i;

	i = 1;
	*ret = 0;
	if (cinfo->array_size == 1)
		return (print_envi_list(shell_data->shell_envi.ordered_envp, 0));
	while (cinfo->cmd_and_args[i])
	{
		key_value = get_key_value(cinfo->cmd_and_args[i]);
		if (key_value)
			edit_env_lists(&shell_data->shell_envi, key_value);
		else
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(cinfo->cmd_and_args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			*ret = 1;
		}
		ft_matrix_free((void ***)&key_value, 0);
		i++;
	}
}
