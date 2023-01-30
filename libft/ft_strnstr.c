/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:46:59 by bamrouch          #+#    #+#             */
/*   Updated: 2022/10/18 15:49:19 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	if (!(*needle))
		return ((char *)haystack);
	while (len > 0 && *(haystack + i) && (i + j) < len)
	{
		while (needle[j] && haystack[i + j] == needle[j] && i + j < len)
		{
			if (j == 0)
				res = (char *)haystack + i;
			j++;
		}
		if (*(needle + j) == 0)
			return (res);
		else
		{
			i++;
			j = 0;
		}
	}
	return (NULL);
}
