/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_managers_helpers_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:19:30 by bamrouch          #+#    #+#             */
/*   Updated: 2023/01/21 19:10:22 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_garbage_collector.h"

void	mem_cut_node(t_list *memory_scope, t_list *to_cut_node)
{
	t_list	*current_node;
	t_list	*prev_node;

	prev_node = memory_scope->content;
	current_node = prev_node->next;
	while (current_node && current_node != to_cut_node)
	{
		prev_node = current_node;
		current_node = current_node->next;
	}
	prev_node->next = current_node->next;
}

void	mem_free_scope(void *scope_lst)
{
	t_list	*mem_scope;
	t_list	*temp_node;

	mem_scope = ((t_list *)scope_lst)->next;
	temp_node = scope_lst;
	free(temp_node->content);
	free(temp_node);
	while (mem_scope)
	{
		temp_node = mem_scope->content;
		ft_lstclear(&temp_node, free);
		temp_node = mem_scope;
		free(temp_node);
		mem_scope = mem_scope->next;
	}
}

void	mem_purge_memory(void)
{
	t_list	*mem_root;
	t_list	*next_scope;

	mem_root = *(memory_root());
	while (mem_root)
	{
		mem_free_scope(mem_root->content);
		next_scope = mem_root->next;
		free(mem_root);
		mem_root = next_scope;
	}
	*(memory_root()) = NULL;
}

// generate a t_mem_params object : parameters goes as follows
// uint64_t scope, void *ref_pointer, uint64_t move_scope
t_mem_manage_params	mem_pass_params(uint64_t scope, ...)
{
	va_list				params;
	t_mem_manage_params	res;

	va_start(params, scope);
	res.node = NULL;
	res.scope = scope;
	res.ref_pointer = va_arg(params, void *);
	res.move_scope = va_arg(params, uint64_t);
	va_end(params);
	return (res);
}
