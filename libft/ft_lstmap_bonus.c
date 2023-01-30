/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:36:02 by bamrouch          #+#    #+#             */
/*   Updated: 2022/10/18 00:16:09 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_make_content(void *content, void *(*f)(void *))
{
	void	*temp;

	temp = f(content);
	if (temp == NULL)
		return (NULL);
	return (temp);
}

static void	*ft_free_empty_list(t_list *lst)
{
	t_list	*temp;
	t_list	*next;

	temp = lst;
	while (temp->next)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	free(temp);
	return (NULL);
}

static t_list	*ft_lst_copy(t_list *lst)
{
	t_list	*temp;
	t_list	*list_head;
	int		list_len;

	if (!lst)
		return (NULL);
	list_len = ft_lstsize(lst) - 1;
	temp = ft_calloc(1, sizeof(t_list));
	if (!temp)
		return (NULL);
	list_head = temp;
	while (list_len--)
	{
		temp->next = ft_calloc(1, sizeof(t_list));
		if (!(temp->next))
			return (ft_free_empty_list(list_head));
		temp = temp->next;
	}
	return (list_head);
}

static void	*ft_free_list(t_list **lst, void (*del)(void *))
{
	ft_lstclear(lst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map_current;
	t_list	*lst_current;
	t_list	*res;

	if (!lst || !f || !del)
		return (NULL);
	map_current = ft_lst_copy(lst);
	if (!map_current)
		return (NULL);
	lst_current = lst;
	res = map_current;
	while (lst_current->next && map_current->next)
	{
		map_current->content = ft_make_content(lst_current->content, f);
		if (!map_current->content)
			return (ft_free_list(&res, del));
		lst_current = lst_current->next;
		map_current = map_current->next;
	}
	map_current->content = ft_make_content(lst_current->content, f);
	if (!map_current->content)
		return (ft_free_list(&res, del));
	return (res);
}
