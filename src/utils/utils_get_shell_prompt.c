/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_shell_prompt.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:55:13 by pablo             #+#    #+#             */
/*   Updated: 2025/11/10 21:27:36 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minishell.h"

/**
 * @brief Creates a colored base prompt string for the minishell.
 *
 * This function constructs a prompt string in the format
 * "Minishell@<USER> " with ANSI color codes applied: "Minishell"
 * in yellow, "@" in red, "<USER>" in blue, and the trailing space
 * in green, followed by a reset to default color.
 *
 * @param envs A pointer to the linked list of environment
 * variables.
 * @return A dynamically allocated string containing the colored
 * prompt, or NULL if memory allocation fails or if the "USER"
 * environment variable is not found.
 */
static char	*create_colored_base_prompt(t_linked_env *envs)
{
	char	*base_prompt;
	char	*colored_prompt;
	char	*user_env;

	user_env = get_enviroment_value("USER", envs);
	if (!user_env)
		return (NULL);
	base_prompt = ft_strjoin(YELLOW "Minishell" RED "@" BLUE, user_env);
	if (!base_prompt)
		return (NULL);
	colored_prompt = ft_strjoin(base_prompt, RESET " " GREEN);
	ft_free((void **)&base_prompt);
	return (colored_prompt);
}

/**
 * @brief Creates a shell prompt string by concatenating a colored prompt
 * with the current directory.
 *
 * This function joins the provided colored prompt and current
 * directory strings to form a complete prompt string for display
 * in the shell.
 *
 * @param colored_prompt The base colored prompt string (e.g., with
 * ANSI color codes).
 * @param current_dir The string representing the current working
 * directory.
 * @return A newly allocated string containing the concatenated
 * prompt and directory, or NULL if either input parameter is NULL
 * or if memory allocation fails.
 */
static char	*create_prompt_with_cwd(char *colored_prompt, char *current_dir)
{
	char	*prompt_with_cwd;

	if (!colored_prompt || !current_dir)
		return (NULL);
	prompt_with_cwd = ft_strjoin(colored_prompt, current_dir);
	return (prompt_with_cwd);
}

/**
 * @brief Finalizes the shell prompt by appending a suffix.
 *
 * This function takes a prompt string that includes the current working
 * directory and appends a reset ANSI code followed by " --> " to create
 * the final prompt. If the input is NULL, it returns NULL.
 *
 * @param prompt_with_cwd The prompt string including the current working
 * directory.
 * @return A new dynamically allocated string with the finalized prompt,
 * or NULL if input is NULL.
 */
static char	*finalize_prompt(char *prompt_with_cwd)
{
	char	*final_prompt;

	if (!prompt_with_cwd)
		return (NULL);
	final_prompt = ft_strjoin(prompt_with_cwd, RESET " --> ");
	return (final_prompt);
}

char	*get_prompt(t_linked_env *envs)
{
	char	*colored_prompt;
	char	*current_dir;
	char	*prompt_with_cwd;
	char	*final_prompt;

	colored_prompt = create_colored_base_prompt(envs);
	if (!colored_prompt)
		return (NULL);
	current_dir = ft_strdup(get_enviroment_value("PWD", envs));
	if (!current_dir)
		return (ft_free((void **)&colored_prompt), NULL);
	prompt_with_cwd = create_prompt_with_cwd(colored_prompt, current_dir);
	ft_free((void **)&colored_prompt);
	ft_free((void **)&current_dir);
	if (!prompt_with_cwd)
		return (NULL);
	final_prompt = finalize_prompt(prompt_with_cwd);
	ft_free((void **)&prompt_with_cwd);
	return (final_prompt);
}
