/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:38:10 by bamrouch          #+#    #+#             */
/*   Updated: 2022/10/17 23:09:56 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	str_len;
	size_t	i;

	if (!s)
		return ;
	i = -1;
	str_len = ft_strlen(s);
	while (++i < str_len)
		write(fd, (s + i), 1);
}
