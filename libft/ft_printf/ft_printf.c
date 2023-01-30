/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:56:58 by bamrouch          #+#    #+#             */
/*   Updated: 2022/11/18 17:32:23 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

ssize_t	ft_manage_converters(va_list args, const char *str,
		t_grouped_flags flags)
{
	ssize_t	printed_chars;

	printed_chars = -1;
	if (str[0] == 'c')
		printed_chars = ft_print_char(va_arg(args, int), &flags);
	else if (str[0] == 's')
		printed_chars = ft_print_str(va_arg(args, char *), &flags);
	else if (str[0] == 'p')
		printed_chars = ft_print_pointer(va_arg(args, unsigned long), &flags);
	else if (str[0] == 'd' || str[0] == 'i')
		printed_chars = ft_print_number(va_arg(args, int), &flags, FALSE);
	else if (str[0] == 'u')
		printed_chars = ft_print_number(va_arg(args, unsigned int), &flags,
				TRUE);
	else if (str[0] == 'x' || str[0] == 'X')
		printed_chars = ft_print_hex_converter(va_arg(args, unsigned int),
				str[0] == 'X',
				&flags);
	else if (str[0] == '%')
		printed_chars = ft_print_percentage(&flags);
	return (printed_chars);
}

int	ft_manage_printf_flags(va_list args, const char *str, size_t *index)
{
	ssize_t			printed_chars;
	size_t			i;
	t_grouped_flags	flags;

	ft_bzero(&flags, sizeof(t_grouped_flags));
	i = ft_parse_flags(str, &flags);
	(*index) += i;
	printed_chars = ft_manage_converters(args, str + i, flags);
	return (printed_chars);
}

int	ft_printf(const char *s, ...)
{
	size_t	i;
	int		printed_chars[2];
	va_list	args;

	if (!s)
		return (-1);
	va_start(args, s);
	i = 0;
	printed_chars[0] = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			printed_chars[1] = ft_manage_printf_flags(args, s + i, &i);
			if (printed_chars[1] >= 0)
				printed_chars[0] += printed_chars[1];
			i++;
			continue ;
		}
		printed_chars[0] += ft_print_char(s[i], NULL);
		i++;
	}
	va_end(args);
	return (printed_chars[0]);
}
