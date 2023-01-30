/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:14:34 by bamrouch          #+#    #+#             */
/*   Updated: 2023/01/21 19:54:49 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_garbage_collector.h"

// returns pointer towards the memory management root node
t_list	**memory_root(void)
{
	static t_list	*memory_root;

	return (&memory_root);
}

// adds an address to an existing scope
//or creates a new scope then adds the memory to it
t_boolean	mem_manage_add(t_mem_manage_params params)
{
	t_list	*memory_scopes;
	t_list	*scope_node;

	memory_scopes = mem_find_scope(params.scope);
	if (!memory_scopes)
		memory_scopes = mem_add_new_scope(params.scope);
	if (params.ref_pointer)
	{
		memory_scopes = mem_find_ref_pointers(memory_scopes,
				params.ref_pointer);
	}
	else
		params.node = create_node_with_content(params.node);
	if (!params.node)
		return (FALSE);
	scope_node = memory_scopes->content;
	ft_lstadd_back(&scope_node, params.node);
	return (TRUE);
}

// moves a memory ref from a scope to another
void	mem_manage_move(t_mem_manage_params params)
{
	t_list	*memory_scope;
	t_list	*move_node;
	t_list	*new_scope;

	if (params.scope == 0 || params.move_scope == 0)
		return ;
	memory_scope = mem_find_scope(params.scope);
	move_node = mem_find_ref_pointers(memory_scope, params.ref_pointer);
	if (move_node == memory_scope)
		return ;
	mem_cut_node(memory_scope, move_node);
	new_scope = mem_find_scope(params.move_scope)->content;
	ft_lstadd_back(&new_scope, move_node);
}

void	ft_free(uint64_t scope, t_boolean purge_all)
{
	t_list	*mem_root;
	t_list	*prev_scope;
	t_list	*temp_scope;

	if (purge_all)
		return (mem_purge_memory());
	mem_root = *(memory_root());
	prev_scope = NULL;
	while (mem_root)
	{
		temp_scope = mem_root->content;
		if (*(uint64_t *)temp_scope->content == scope)
		{
			mem_free_scope(temp_scope);
			if (!prev_scope)
				*(memory_root()) = mem_root->next;
			else
				prev_scope->next = mem_root->next;
			free(mem_root);
			return ;
		}
		prev_scope = mem_root;
		mem_root = mem_root->next;
	}
}

void	*ft_malloc(uint64_t size, t_mem_manage_params params)
{
	void	*temp;
	t_list	*temp_l;

	if (!size || params.scope == 0)
		return (NULL);
	temp = malloc(size);
	if (!temp)
		return (ft_free(0, TRUE), NULL);
	temp_l = create_node_with_content(temp);
	if (!temp_l)
	{
		free(temp);
		return (ft_free(0, TRUE), NULL);
	}
	params.node = temp_l;
	if (mem_manage_add(params))
		return (temp);
	return (NULL);
}
