/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:58:44 by bamrouch          #+#    #+#             */
/*   Updated: 2023/01/31 18:49:07 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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