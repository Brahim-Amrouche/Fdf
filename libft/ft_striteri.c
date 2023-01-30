/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:46:20 by bamrouch          #+#    #+#             */
/*   Updated: 2022/10/17 22:58:37 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	str_len;
	size_t	i;

	if (!s || !f)
		return ;
	str_len = ft_strlen(s);
	i = -1;
	while (++i < str_len)
		f(i, (s + i));
}
