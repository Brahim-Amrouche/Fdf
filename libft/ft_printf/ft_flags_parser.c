/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:21:24 by bamrouch          #+#    #+#             */
/*   Updated: 2022/11/18 17:32:56 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	ft_is_flag(int c)
{
	if (c == '0' || c == '-' || c == ' ' || c == '#' || c == '+' || c == '.')
		return (1);
	return (0);
}

static size_t	ft_handle_initial_flags(const char *str, t_grouped_flags *flags)
{
	size_t	i;

	i = 0;
	while (ft_is_flag(str[++i]))
	{
		if (str[i] == '0')
			flags->zero = TRUE;
		else if (str[i] == '-')
			flags->minus = TRUE;
		else if (str[i] == '#')
			flags->format = TRUE;
		else if (str[i] == '+')
			flags->plus = TRUE;
		else if (str[i] == ' ')
			flags->space = TRUE;
		else if (str[i] == '.')
		{
			flags->precision = TRUE;
			i++;
			break ;
		}
	}
	return (i);
}

size_t	ft_print_percentage(t_grouped_flags *flags)
{
	ssize_t	printed_chars;

	printed_chars = 0;
	printed_chars += ft_handle_zero_flag(flags, 1, FALSE, 0);
	printed_chars += ft_print_char('%', flags);
	return (printed_chars);
}

size_t	ft_handle_format_flag(t_grouped_flags *flags, t_boolean is_upper,
	ssize_t p)
{
	ssize_t	printed_chars;

	printed_chars = 0;
	if (flags && flags->format && p != 0)
	{
		if (is_upper)
			printed_chars += ft_print_str("0X", NULL);
		else
			printed_chars += ft_print_str("0x", NULL);
	}
	return (printed_chars);
}

size_t	ft_parse_flags(const char *str, t_grouped_flags *flags)
{
	size_t	i;

	i = ft_handle_initial_flags(str, flags);
	if (flags->precision)
		flags->precision_size = ft_atoi(&str[i]);
	else
		flags->offset_size = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	if (!(flags->minus) && !(flags->zero) && flags->offset_size > 0)
		flags->left_padding = TRUE;
	if (str[i] && str[i] == '.' && !(flags->precision))
	{
		flags->precision = TRUE;
		flags->precision_size = ft_atoi(&str[++i]);
		while (ft_isdigit(str[i]))
			i++;
	}
	return (i);
}
