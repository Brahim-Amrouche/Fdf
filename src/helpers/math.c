/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:58:44 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/11 15:48:58 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

double	degree_to_rad(int degree)
{
	return (degree * ((double)M_PI) /(double) 180.0);
}

int	ft_abs(int x)
{
	if (x < 0)
		return -x;
	return x;
}

double floating_point(double x)
{
	if (x > 0)
		return x - (int) x;
	else
		return x - (int)x - 1;
}

t_boolean	ft_str_is_integer(const char *str, int	*res)
{
	int		i;
	long	temp;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (FALSE);
	while (str[i] && str[i] != ',')
		if (i > 11 || !ft_isdigit(str[i++]))
			return (FALSE);
	temp = ft_atoi(str);
	if (temp > INT_MAX || temp < INT_MIN)
		return (FALSE);
	*res = (int) temp;
	return (TRUE);
}