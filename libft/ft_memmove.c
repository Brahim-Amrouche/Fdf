/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 00:42:22 by bamrouch          #+#    #+#             */
/*   Updated: 2022/10/16 01:42:23 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*source;

	if (!dst && !src && len)
		return (dst);
	dest = (char *)dst;
	source = (char *)src;
	if (dest > source)
		while (len-- > 0)
			dest[len] = source[len];
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
