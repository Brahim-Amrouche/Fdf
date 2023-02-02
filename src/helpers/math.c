/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:58:44 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/02 22:32:54 by bamrouch         ###   ########.fr       */
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

t_boolean	string_is_hex(char *str)
{
	size_t i;
	if (!(str[0] && str[1] && str[0] == '0' && ( str[1] == 'X'  || str[1] == 'x' )))
		return FALSE;
	i = 2;
	while (str[i])
	{
		if (!(i < 8 || ft_isdigit(str[i]) || ft_strchr("abcdefABCDEF", str[i])))
			return FALSE;
		i++;
	}
	return TRUE;
}

t_boolean	ft_str_is_hex(char *str, int *res)
{
	size_t i;
	int		coef;

	if (!string_is_hex(str))
		return FALSE;
	str += 2;
	i = ft_strlen(str);
	coef = 1;
	*res = 0;
	while (i-- >= 0)
	{
		(*res) += coef * 15;//the number in hex
		coef *= 16;
	}
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