/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 21:07:11 by bamrouch          #+#    #+#             */
/*   Updated: 2023/01/17 21:43:10 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int				ft_printf(const char *s, ...);

typedef enum e_boolean
{
	FALSE = 0,
	TRUE = 1
}				t_boolean;

typedef struct s_grouped_flags
{
	t_boolean	format;
	t_boolean	precision;
	t_boolean	plus;
	t_boolean	space;
	t_boolean	minus;
	t_boolean	zero;
	t_boolean	left_padding;
	ssize_t		offset_size;
	ssize_t		precision_size;
}				t_grouped_flags;

/* Converters Logic */
size_t			ft_print_char(char c, t_grouped_flags *flags);
size_t			ft_print_str(char *str, t_grouped_flags *flags);
size_t			ft_hex_len(unsigned long value);
size_t			ft_print_hex(unsigned long value, t_boolean upper);
size_t			ft_print_pointer(unsigned long p, t_grouped_flags *flags);
size_t			ft_print_hex_converter(unsigned long p, t_boolean is_upper,
					t_grouped_flags *flags);
size_t			ft_decimal_len(long d);
size_t			ft_print_decimal(long d);
size_t			ft_print_number(long i, t_grouped_flags *flags,
					t_boolean is_unsigned);
size_t			ft_print_percentage(t_grouped_flags *flags);
/* end Converts Logic */

/* Flags Logic */
ssize_t			ft_handle_minus_flag(t_grouped_flags *flags,
					ssize_t printed_len);
ssize_t			ft_handle_zero_flag(t_grouped_flags *flags, ssize_t printed_len,
					t_boolean is_number_precision, ssize_t decimal_len);
ssize_t			ft_handle_plus_and_space_flag(t_grouped_flags *flags, long i,
					t_boolean is_unsigned);
ssize_t			ft_handle_left_padding(t_grouped_flags *flags,
					ssize_t printed_len,
					t_boolean is_number_precision);
ssize_t			ft_handle_precision_offset(t_grouped_flags *flags,
					ssize_t printable_len,
					ssize_t printable_mod,
					ssize_t precision_mod);
size_t			ft_handle_format_flag(t_grouped_flags *flags,
					t_boolean is_upper, ssize_t p);
size_t			ft_parse_flags(const char *str, t_grouped_flags *flags);
/* end Flags Logic*/

#endif