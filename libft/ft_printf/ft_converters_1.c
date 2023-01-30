/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converters_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:02:26 by bamrouch          #+#    #+#             */
/*   Updated: 2022/11/18 17:55:48 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

size_t	ft_print_char(char c, t_grouped_flags *flags)
{
	ssize_t	printed_chars;

	printed_chars = 1;
	printed_chars += ft_handle_left_padding(flags, 1, FALSE);
	ft_putchar_fd(c, 1);
	printed_chars += ft_handle_minus_flag(flags, 1);
	return (printed_chars);
}

size_t	ft_print_str(char *str, t_grouped_flags *flags)
{
	ssize_t	printed_chars;
	ssize_t	i;

	if (!str)
		return (ft_print_str("(null)", flags));
	printed_chars = 0;
	if (flags && (flags->precision_size > (ssize_t)ft_strlen(str)
			|| !(flags->precision)))
		printed_chars = ft_handle_left_padding(flags, ft_strlen(str), FALSE);
	else if (flags)
		printed_chars = ft_handle_left_padding(flags, flags->precision_size,
				FALSE);
	i = 0;
	while ((str[i] && (!flags || !(flags->precision))) || (flags
			&& flags->precision && str[i] && i < flags->precision_size))
		ft_putchar_fd(str[i++], 1);
	printed_chars += i;
	printed_chars += ft_handle_minus_flag(flags, printed_chars);
	return (printed_chars);
}

size_t	ft_print_pointer(unsigned long p, t_grouped_flags *flags)
{
	ssize_t	printed_chars;

	printed_chars = 0;
	printed_chars += ft_handle_left_padding(flags, ft_hex_len(p) + 2, FALSE);
	printed_chars += ft_print_str("0x", NULL) + ft_print_hex(p, FALSE);
	printed_chars += ft_handle_minus_flag(flags, printed_chars);
	return (printed_chars);
}

size_t	ft_print_number(long i, t_grouped_flags *flags, t_boolean is_unsigned)
{
	ssize_t	printed_chars;
	ssize_t	decimal_len;

	printed_chars = 0;
	decimal_len = ft_decimal_len(i) + (!is_unsigned && i >= 0 && (flags->plus
				|| flags->space)) - (flags->precision && i == 0
			&& flags->precision_size == 0);
	printed_chars += ft_handle_precision_offset(flags, decimal_len, 0, (i < 0)
			+ (!is_unsigned && i >= 0 && (flags->plus || flags->space)));
	printed_chars += ft_handle_plus_and_space_flag(flags, i, is_unsigned);
	if (i < 0)
	{
		printed_chars += ft_print_char('-', NULL);
		i *= -1;
	}
	printed_chars += ft_handle_zero_flag(flags, decimal_len, flags->precision,
			ft_decimal_len(i));
	if (!(flags->precision && i == 0 && flags->precision_size == 0))
		printed_chars += ft_print_decimal(i);
	printed_chars += ft_handle_minus_flag(flags, printed_chars);
	return (printed_chars);
}

size_t	ft_print_hex_converter(unsigned long p, t_boolean is_upper,
		t_grouped_flags *flags)
{
	ssize_t	printed_chars;
	ssize_t	hex_len;

	hex_len = ft_hex_len(p) - (flags->precision && p == 0
			&& flags->precision_size == 0);
	printed_chars = 0;
	if (flags->format && p != 0)
		hex_len += 2;
	printed_chars += ft_handle_precision_offset(flags,
			ft_hex_len(p),
			2 * (flags->format && p != 0)
			- (flags->precision && p == 0 && flags->precision_size == 0),
			2 * (flags->format && p != 0));
	printed_chars += ft_handle_format_flag(flags, is_upper, p);
	printed_chars += ft_handle_zero_flag(flags, hex_len, flags->precision,
			ft_hex_len(p));
	if (!(flags->precision && p == 0 && flags->precision_size == 0))
		printed_chars += ft_print_hex(p, is_upper);
	printed_chars += ft_handle_minus_flag(flags, printed_chars);
	return (printed_chars);
}
