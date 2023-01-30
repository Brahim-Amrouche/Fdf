/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:16:35 by bamrouch          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:09 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 && !s2)
		return (0);
	i = 0;
	while ((*(s1 + i) || *(s2 + i)) && i < n)
	{
		if (((unsigned char)*(s1 + i)) != ((unsigned char)*(s2 + i)))
			return (((unsigned char)*(s1 + i)) - ((unsigned char)*(s2 + i)));
		i++;
	}
	return (0);
}
