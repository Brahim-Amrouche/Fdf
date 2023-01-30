/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:34:55 by bamrouch          #+#    #+#             */
/*   Updated: 2022/10/13 02:14:51 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	s_len;
	size_t	i;
	char	*res;

	s_len = ft_strlen(s1);
	res = (char *)ft_calloc(s_len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
