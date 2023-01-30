/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:02:23 by bamrouch          #+#    #+#             */
/*   Updated: 2022/10/18 15:09:02 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	if (!dst && !dstsize)
		return (src_len);
	dst_len = ft_strlen(dst);
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
