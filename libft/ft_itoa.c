/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 03:10:30 by bamrouch          #+#    #+#             */
/*   Updated: 2022/10/17 22:42:03 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_char_size(int c)
{
	size_t	len;

	len = 1;
	if (c == -2147483648)
		return (12);
	else if (c < 0)
	{
		c *= -1;
		len++;
	}
	while (c / 10 > 0)
	{
		len++;
		c /= 10;
	}
	return (len + 1);
}

static void	ft_itoi_logic(char *res, size_t char_size, int c)
{
	while (--char_size > 0)
	{
		res[char_size - 1] = (c % 10) + '0';
		c /= 10;
	}
}

char	*ft_itoa(int c)
{
	size_t	char_size;
	int		positive;
	char	*res;

	char_size = ft_char_size(c);
	res = ft_calloc(char_size, sizeof(char));
	if (!res)
		return (NULL);
	positive = 1;
	if (c == -2147483648)
	{
		ft_strlcpy(res, "-2147483648", 12);
		return (res);
	}
	else if (c < 0)
	{
		c *= -1;
		positive = 0;
	}
	ft_itoi_logic(res, char_size, c);
	if (!positive)
		res[0] = '-';
	return (res);
}
