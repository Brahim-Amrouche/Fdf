/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:52:48 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/14 18:19:15 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_boolean	check_hex_format(char *str)
{
	size_t	i;

	if (*str && *(str++) == ',')
		if (!(*str && *(str++) == '0' && (*(str) == 'X' || *(str) == 'x')
				&& *(++str)))
			return (FALSE);
	i = 0;
	while (str[i])
	{
		if (!(i < 6 && (ft_isdigit(str[i]) || (str[i] >= 'A' && str[i] <= 'F')
					|| (str[i] >= 'a' && str[i] <= 'f'))))
			return (FALSE);
		i++;
	}
	if (i % 2)
		return (FALSE);
	return (TRUE);
}

static unsigned int	hex_char_to_number(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	return (0);
}

t_boolean	ft_str_is_hex(char *str, int *res)
{
	ssize_t			i;
	unsigned int	coef;

	*res = 0;
	while (*str && *str != ',')
		str++;
	if (!check_hex_format(str))
		return (FALSE);
	i = ft_strlen(str);
	coef = 1;
	while (--i >= 0)
	{
		(*res) = *res + coef * hex_char_to_number(str[i]);
		coef *= 16;
	}
	return (TRUE);
}
