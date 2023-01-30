/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:33:20 by bamrouch          #+#    #+#             */
/*   Updated: 2022/10/17 22:54:46 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	str_len;
	size_t	i;
	char	*res;

	if (!s)
		return (NULL);
	if (!f)
		return (ft_strdup(s));
	str_len = ft_strlen(s);
	res = (char *)ft_calloc(str_len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < str_len)
		res[i] = f(i, s[i]);
	return (res);
}
