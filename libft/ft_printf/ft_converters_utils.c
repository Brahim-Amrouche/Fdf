/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converters_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:06:19 by bamrouch          #+#    #+#             */
/*   Updated: 2022/11/18 17:30:55 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

size_t	ft_hex_len(unsigned long value)
{
	size_t	len;

	len = 0;
	if (value >= 16)
	{
		len += ft_hex_len(value / 16);
		len += ft_hex_len(value % 16);
	}
	else
		len++;
	return (len);
}

size_t	ft_print_hex(unsigned long value, t_boolean upper)
{
	size_t	len;

	len = 0;
	if (value >= 16)
	{
		len += ft_print_hex(value / 16, upper);
		len += ft_print_hex(value % 16, upper);
		return (len);
	}
	else
	{
		if (value <= 9)
			return (ft_print_char("0123456789"[value], NULL));
		else if (upper)
			return (ft_print_char("ABCDEF"[value % 10], NULL));
		else
			return (ft_print_char("abcdef"[value % 10], NULL));
	}
}

size_t	ft_decimal_len(long d)
{
	size_t	len;

	len = 0;
	if (d < 0)
	{
		len++;
		len += ft_decimal_len(d * -1);
	}
	else if (d > 9)
	{
		len += ft_decimal_len(d / 10);
		len += ft_decimal_len(d % 10);
	}
	else
		len += 1;
	return (len);
}

size_t	ft_print_decimal(long d)
{
	size_t	len;

	len = 0;
	if (d < 0)
	{
		d *= -1;
		len += ft_print_char('-', NULL);
		len += ft_print_decimal(d);
	}
	else if (d > 9)
	{
		len += ft_print_decimal(d / 10);
		len += ft_print_decimal(d % 10);
	}
	else
		len += ft_print_char(d + '0', NULL);
	return (len);
}

ssize_t	ft_handle_precision_offset(t_grouped_flags *flags,
	ssize_t printable_len,
	ssize_t printable_mod,
	ssize_t precision_mod)
{
	ssize_t	printed_char;

	printed_char = 0;
	if (!flags)
		return (0);
	if (printable_len > flags->precision_size || !(flags->precision))
		printed_char += ft_handle_left_padding(flags, printable_len
				+ printable_mod, flags->precision);
	else
		printed_char += ft_handle_left_padding(flags, flags->precision_size
				+ precision_mod, flags->precision);
	return (printed_char);
}
