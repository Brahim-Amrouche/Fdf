/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:42:21 by bamrouch          #+#    #+#             */
/*   Updated: 2022/11/18 17:55:40 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	res;
	int				sign;

	res = 0;
	i = -1;
	sign = 1;
	while (ft_isspace(*(str + (++i))))
		;
	if (*(str + i) == '+' || *(str + i) == '-')
	{
		if (*(str + i) == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(*(str + i)))
	{
		res = (10 * res) + ((*(str + i)) - '0');
		if (res >= 9223372036854775807 && sign == 1)
			return (-1);
		else if (res >= 9223372036854775807 && sign == -1)
			return (0);
		i++;
	}
	return (res * sign);
}
