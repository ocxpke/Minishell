/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:45:00 by pablo             #+#    #+#             */
/*   Updated: 2025/10/27 10:45:42 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_char_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		printf("|%s|\n", matrix[i]);
		i++;
	}
}

static char	*get_token_type_name(t_ttype type)
{
	if (type == ARGUMENT)
		return ("ARGUMENT");
	else if (type == COMMAND_ROUTE)
		return ("COMMAND_ROUTE");
	else if (type == COMMAND_BUILT_IN)
		return ("COMMAND_BUILT_IN");
	else if (type == HEREDOC_EOF)
		return ("HEREDOC_EOF");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == REDIRECT_IN_CHAR)
		return ("REDIRECT_IN_CHAR");
	else if (type == REDIRECT_IN_CHAR_HEREDOC)
		return ("REDIRECT_IN_CHAR_HEREDOC");
	else if (type == REDIRECT_OUT_CHAR)
		return ("REDIRECT_OUT_CHAR");
	else if (type == REDIRECT_OUT_CHAR_APPEND)
		return ("REDIRECT_OUT_CHAR_APPEND");
	else if (type == REDIRECT_IN_ROUTE)
		return ("REDIRECT_IN_ROUTE");
	else if (type == REDIRECT_OUT_ROUTE)
		return ("REDIRECT_OUT_ROUTE");
	else if (type == UNDEFINED)
		return ("UNDEFINED");
	else
		return ("UNKNOWN");
}

void	print_token_matrix(t_token **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
	{
		printf("Token matrix is NULL\n");
		return ;
	}
	printf("=== TOKEN MATRIX DEBUG ===\n");
	while (tokens[i])
	{
		printf("[%d] String: |%s| -> Type: %s\n",
			i,
			tokens[i]->string ? tokens[i]->string : "NULL",
			get_token_type_name(tokens[i]->token_type));
		i++;
	}
	printf("=== END TOKEN MATRIX ===\n");
}

void	print_single_token(t_token *token, int index)
{
	if (!token)
	{
		printf("Token[%d] is NULL\n", index);
		return ;
	}
	printf("=== SINGLE TOKEN DEBUG ===\n");
	printf("Index: %d\n", index);
	printf("String: |%s|\n", token->string ? token->string : "NULL");
	printf("Type: %s\n", get_token_type_name(token->token_type));
	printf("=== END SINGLE TOKEN ===\n");
}

void	print_cinfo(t_cinfo *cinfo, int index)
{
	if (!cinfo)
	{
		printf("Cinfo[%d] is NULL\n", index);
		return ;
	}
	printf("=== CINFO[%d] DEBUG ===\n", index);
	printf("Input file: %s\n", cinfo->input_file);
	printf("Output file: %s\n", cinfo->output_file);
	printf("Is append: %d\n", cinfo->is_append);
	printf("Is heredoc: %d\n", cinfo->is_heredoc);
	printf("Command: %s\n", cinfo->command);
	printf("Args:\n");
	if (cinfo->args)
		print_char_matrix(cinfo->args);
	else
		printf("NULL\n");
	printf("=== END CINFO[%d] ===\n", index);
}

void	print_cinfos(t_cinfo **cinfos)
{
	int	i;

	i = 0;
	if (!cinfos)
	{
		printf("Cinfos is NULL\n");
		return ;
	}
	printf("=== CINFOS DEBUG ===\n");
	while (cinfos[i])
	{
		print_cinfo(cinfos[i], i);
		i++;
	}
	printf("=== END CINfos ===\n");
}

void	print_piped_info(t_piped_info *piped_info)
{
	t_piped_info	*current;

	if (!piped_info)
	{
		printf("Piped info is NULL\n");
		return ;
	}
	printf("=== PIPED INFO DEBUG ===\n");
	current = piped_info;
	while (current)
	{
		printf("PID: %d, File command name: %s\n", current->pid,
			current->file_cmmd_name ? current->file_cmmd_name : "NULL");
		current = current->next;
	}
	printf("=== END PIPED INFO ===\n");
}

void	print_einfo(t_einfo *einfo)
{
	if (!einfo)
	{
		printf("Einfo is NULL\n");
		return ;
	}
	printf("=== EINFO DEBUG ===\n");
	printf("N pipes: %d\n", einfo->n_pipes);
	print_cinfos(einfo->cinfos);
	print_piped_info(einfo->piped_info);
	printf("=== END EINFO ===\n");
}

extern void	print_envi_list(t_linked_env *envp_list, int mode);

void	print_shell_envi(t_envp *shell_envi)
{
	if (!shell_envi)
	{
		printf("Shell envi is NULL\n");
		return ;
	}
	printf("=== SHELL ENVI DEBUG ===\n");
	printf("Len env: %d\n", shell_envi->len_env);
	printf("Envp:\n");
	if (shell_envi->envp)
		print_envi_list(shell_envi->envp, 1);
	else
		printf("NULL\n");
	printf("Ordered envp:\n");
	if (shell_envi->ordered_envp)
		print_envi_list(shell_envi->ordered_envp, 1);
	else
		printf("NULL\n");
	printf("Envp exec:\n");
	if (shell_envi->envp_exec)
		print_char_matrix(shell_envi->envp_exec);
	else
		printf("NULL\n");
	printf("=== END SHELL ENVI ===\n");
}

void	debug_shell_info(t_shell_data *shell_data)
{
	if (!shell_data)
	{
		printf("Shell data is NULL\n");
		return ;
	}
	printf("========================================\n");
	printf("========== SHELL INFO DEBUG ============\n");
	printf("========================================\n");
	print_shell_envi(&shell_data->shell_envi);
	printf("\n");
	print_token_matrix(shell_data->tokens);
	printf("\n");
	printf("PID fork: %d\n", shell_data->pid_fork);
	printf("\n");
	print_einfo(shell_data->einfo);
	printf("========================================\n");
	printf("======= END SHELL INFO DEBUG ==========\n");
	printf("========================================\n");
}

char	*generate_cmmd_file_name(int index)
{
	char	*tmp_name;
	char	*tmp_n;

	tmp_n = ft_itoa(index);
	if (!tmp_n)
		return (NULL);
	tmp_name = ft_strjoin("cmd_", tmp_n);
	if (!tmp_name)
		return (ft_free((void **)&tmp_n), NULL);
	ft_free((void **)&tmp_n);
	tmp_n = ft_strjoin(tmp_name, ".tmp");
	ft_free((void **)&tmp_name);
	if (!tmp_n)
		return (NULL);
	return (tmp_n);
}

int	generate_cmmd_file(char *file_name, char *cmmd_to_write)
{
	int	fd;

	if (!file_name || !cmmd_to_write)
		return (0);
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (0);
	if (write(fd, cmmd_to_write, ft_strlen(cmmd_to_write)) == -1)
	{
		close(fd);
		return (0);
	}
	if (write(fd, "\n", 1) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

