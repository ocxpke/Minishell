/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:27:04 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/13 20:22:05 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_error(t_list **start, t_list *new, void (*del)(void *))
{
	ft_lstclear(start, del);
	ft_lstdelone(new, del);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	int		lst_len;
	t_list	*new_lst_start;
	t_list	*tmp_new_lst;

	if (!lst)
		return (NULL);
	lst_len = ft_lstsize(lst);
	new_lst_start = ft_lstnew(f(lst->content));
	if (!new_lst_start)
		return (NULL);
	lst = lst->next;
	if (!lst)
		return (new_lst_start);
	while (--lst_len)
	{
		tmp_new_lst = ft_lstnew(f(lst->content));
		if (!tmp_new_lst)
		{
			free_error(&new_lst_start, tmp_new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst_start, tmp_new_lst);
		lst = lst->next;
	}
	return (new_lst_start);
}
