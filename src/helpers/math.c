/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:58:44 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/19 15:55:57 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	degree_to_rad(int degree)
{
	return (degree * ((double)M_PI) / (double)180.0);
}

long	ft_abs(long x)
{
	if (x < 0)
		return (-x);
	return (x);
}

double	floating_point(double x)
{
	if (x > 0)
		return (x - (int)x);
	else
		return (x - (int)x - 1);
}

t_boolean	ft_str_is_integer(const char *str, int *res)
{
	int		i;
	long	temp;
	long	is_neg;

	is_neg = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			is_neg = -1;
		str++;
	}
	if (!ft_isdigit(*str))
		return (FALSE);
	while (*str == '0')
		str++;
	i = 0;
	while (str[i] && str[i] != ',')
		if (i > 10 || !ft_isdigit(str[i++]))
			return (FALSE);
	temp = ft_atoi(str) * is_neg;
	if (temp > INT_MAX || temp < INT_MIN)
		return (FALSE);
	*res = (int)temp;
	return (TRUE);
}
