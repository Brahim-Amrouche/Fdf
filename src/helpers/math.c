/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:58:44 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/01 13:38:03 by bamrouch         ###   ########.fr       */
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

t_boolean	ft_str_is_integer(const char *str, long *res)
{
	int		i;
	long	temp;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (FALSE);
	while (str[i] && !ft_is_space(str[i]))
		if (i > 11 || !ft_isdigit(str[i++]))
			return (FALSE);
	temp = ft_atoi(str);
	if (temp > INT_MAX || temp < INT_MIN)
		return (FALSE);
	*res = temp;
	return (TRUE);
}