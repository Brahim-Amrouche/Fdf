/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_applier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:07:27 by bamrouch          #+#    #+#             */
/*   Updated: 2022/11/18 17:11:55 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

ssize_t	ft_print_offset_flags(char c, ssize_t offset_size, ssize_t printed_len)
{
	ssize_t	offset;

	offset = offset_size - printed_len;
	while (offset-- > 0)
		ft_putchar_fd(c, 1);
	if (offset_size >= printed_len)
		return (offset_size - printed_len);
	return (0);
}

ssize_t	ft_handle_minus_flag(t_grouped_flags *flags, ssize_t printed_len)
{
	if (flags && flags->minus)
		return (ft_print_offset_flags(' ', flags->offset_size, printed_len));
	return (0);
}

ssize_t	ft_handle_zero_flag(t_grouped_flags *flags, ssize_t printed_len,
		t_boolean is_number_precision, ssize_t decimal_len)
{
	if (flags && flags->zero && !(flags->minus) && !is_number_precision)
		return (ft_print_offset_flags('0', flags->offset_size, printed_len));
	if (flags && is_number_precision)
		return (ft_print_offset_flags('0', flags->precision_size, decimal_len));
	return (0);
}

ssize_t	ft_handle_plus_and_space_flag(t_grouped_flags *flags, long i,
		t_boolean is_unsigned)
{
	if (flags && !is_unsigned && flags->plus && i >= 0)
		return (ft_print_char('+', NULL));
	else if (flags && !is_unsigned && flags->space && i >= 0)
		return (ft_print_char(' ', NULL));
	return (0);
}

ssize_t	ft_handle_left_padding(t_grouped_flags *flags, ssize_t printed_len,
		t_boolean is_number_precision)
{
	if (flags && flags->left_padding && !is_number_precision)
		return (ft_print_offset_flags(' ', flags->offset_size, printed_len));
	if (flags && is_number_precision && !(flags->minus))
		return (ft_print_offset_flags(' ', flags->offset_size, printed_len));
	return (0);
}
