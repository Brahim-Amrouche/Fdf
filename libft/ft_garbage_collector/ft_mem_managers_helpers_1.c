/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_managers_helpers_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:06:10 by bamrouch          #+#    #+#             */
/*   Updated: 2023/01/21 20:20:17 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_garbage_collector.h"

// finds a reference pointer this case is very important for included pointers 
// for example **p includes *p so they need to be related
t_list	*mem_find_ref_pointers(t_list *memory_scope, void *ref_pointer)
{
	t_list	*mem_scope_inner_nodes;
	t_list	*current_node;

	if (!memory_scope || !ref_pointer)
		return (NULL);
	mem_scope_inner_nodes = memory_scope->content;
	mem_scope_inner_nodes = mem_scope_inner_nodes->next;
	while (mem_scope_inner_nodes)
	{
		current_node = mem_scope_inner_nodes->content;
		while (current_node && current_node->content != ref_pointer)
			current_node = current_node->next;
		if (!current_node)
			mem_scope_inner_nodes = mem_scope_inner_nodes->next;
		return (mem_scope_inner_nodes);
	}
	return (memory_scope);
}

// a copy of ft_lstnew
t_list	*create_node_with_content(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (ft_free(0, TRUE), NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// adds a scope key if not already existing
t_list	*mem_add_new_scope(uint64_t scope)
{
	uint64_t	*key;
	t_list		*scope_first_node;
	t_list		*scope_node;

	key = malloc(sizeof(uint64_t));
	if (!key)
		return (NULL);
	*key = scope;
	scope_first_node = create_node_with_content(key);
	if (!scope_first_node)
	{
		free(key);
		return (NULL);
	}
	scope_node = create_node_with_content(scope_first_node);
	if (!scope_node)
	{
		ft_lstclear(&scope_first_node, free);
		return (NULL);
	}
	ft_lstadd_back(memory_root(), scope_node);
	return (scope_node);
}

// finds a scope with it's key
t_list	*mem_find_scope(uint64_t scope)
{
	t_list		*memory_scopes;
	uint64_t	memory_scope_key;

	memory_scopes = *(memory_root());
	while (memory_scopes)
	{
		memory_scope_key = *(uint64_t *)
			((t_list *)memory_scopes->content)->content;
		if (memory_scope_key == scope)
			break ;
		memory_scopes = memory_scopes->next;
	}
	return (memory_scopes);
}

// prints the memory state for debuging purposes
// void	ft_print_memory(void)
// {
// 	t_list	*mem_root;
// 	t_list	*scope_node;
// 	t_list	*memory_node;
// 	size_t	mem_nodes_counter;

// 	mem_root = *memory_root();
// 	while (mem_root)
// 	{
// 		scope_node = mem_root->content;
// 		ft_printf("for scope_id %d\n", *(uint64_t *)scope_node->content);
// 		scope_node = scope_node->next;
// 		mem_nodes_counter = 1;
// 		while (scope_node)
// 		{
// 			memory_node = scope_node->content;
// 			ft_printf("	this memory node %d\n", mem_nodes_counter);
// 			while (memory_node)
// 			{
// 				ft_printf("		address %p\n", memory_node->content);
// 				memory_node = memory_node->next;
// 			}
// 			mem_nodes_counter++;
// 			scope_node = scope_node->next;
// 		}
// 		ft_printf("end of scope node with %d nodes\n", --mem_nodes_counter);
// 		mem_root = mem_root->next;
// 	}
// }
