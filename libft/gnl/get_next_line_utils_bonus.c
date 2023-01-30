/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 01:07:39 by bamrouch          #+#    #+#             */
/*   Updated: 2023/01/19 17:43:24 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_gnl_strlen(char *s)
{
	size_t	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*res;

	if (count && size > SIZE_MAX / count)
		return (0);
	res = (char *)malloc(count * size);
	if (!res)
		return (NULL);
	i = 0;
	while (i < count * size)
		res[i++] = '\0';
	return (res);
}

size_t	ft_gnl_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_gnl_strlen(src);
	if (!dst && !dstsize)
		return (src_len);
	dst_len = ft_gnl_strlen(dst);
	i = 0;
	if (dstsize <= dst_len || dstsize == 0)
		return (src_len + dstsize);
	while (i < dstsize - dst_len - 1 && i < src_len)
	{
		dst[(dst_len + i)] = src[i];
		i++;
	}
	dst[(dst_len + i)] = '\0';
	return (src_len + dst_len);
}

ssize_t	ft_strchr_index(char *s, int c)
{
	char	*temp;
	ssize_t	i;

	if (!s)
		return (-1);
	temp = (char *)s;
	i = 0;
	while (*(temp + i))
	{
		if (*(temp + i) == (char)c)
			return (i);
		i++;
	}
	return (-1);
}
