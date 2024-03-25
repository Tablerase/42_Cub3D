/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:09:33 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/25 11:53:35 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Program name: `libftprintf.a`

Turn in files: Makefile, *.h, *.c

Makefile: `NAME, all, clean, fclean, re`

External functs: `malloc, free, write,
va_start, va_arg, va_copy, va_end`

Return value: Number of char printed 

Libft authorized: Yes

Description: Write a library that contains ft_printf(), 
a function that will mimic the original printf()

- %c Prints a single character.
- %s Prints a string (as defined by the common C convention).
- %p The void * pointer argument has to be printed in hexadecimal format.
- %d Prints a decimal (base 10) number.
- %i Prints an integer in base 10.
- %u Prints an unsigned decimal (base 10) number.
- %x Prints a number in hexadecimal (base 16) lowercase format.
- %X Prints a number in hexadecimal (base 16) uppercase format.
- %% Prints a percent sign.
*/

#include "../../Includes/libft.h"
#include "../../Includes/ft_printf.h"

/*
Max long long: 9223372036854775807
- Len 19 char
- Binary Len: 64 char, Use for reusability in other case
*/
static int	ft_print_num(long long num, char type)
{
	int		printed;
	char	*str;

	printed = 0;
	str = ft_calloc(64 + 1, sizeof(char));
	if (!str)
		return (printed);
	if (type == 'i')
		ft_putnbr_base(num, "0123456789", str);
	if (type == 'u')
		ft_putnbr_base(num, "0123456789", str);
	if (type == 'x')
		ft_putnbr_base(num, "0123456789abcdef", str);
	if (type == 'X')
		ft_putnbr_base(num, "0123456789ABCDEF", str);
	if (num < 0)
	{
		printed += write(1, "-", 1);
		printed += ft_reverse_print_str(str + 1);
	}
	else
		printed += ft_reverse_print_str(str);
	free(str);
	return (printed);
}

// print address
// allocation: size of max long long len: 7FFFFFFFFFFFFFFF -> 17 char 
static int	ft_print_address(unsigned long long address)
{
	char				*str;
	int					printed;

	printed = 0;
	if (!address)
	{
		printed += write(1, "(nil)", 5);
		return (printed);
	}
	str = ft_calloc(17 + 1, sizeof(char));
	ft_uputnbr_base(address, "0123456789abcdef", str);
	printed += write(1, "0x", 2);
	printed += ft_reverse_print_str(str);
	free(str);
	return (printed);
}

//check parse of % end return the type as a char.
// %x only search if x is a wanted tags.
// tags: cspdiuxX%
static int	ft_print_type(va_list argument, char c)
{
	int	result;

	result = 0;
	if (c == 'c')
		result += ft_print_char((char)va_arg(argument, int));
	if (c == 's')
		result += ft_print_str(va_arg(argument, char *));
	if (c == '%')
		result += write(1, "%", 1);
	if (c == 'i' || c == 'd')
		result += ft_print_num(va_arg(argument, int), 'i');
	if (c == 'u')
		result += ft_print_num(va_arg(argument, unsigned int), 'u');
	if (c == 'x')
		result += ft_print_num(va_arg(argument, unsigned int), 'x');
	if (c == 'X')
		result += ft_print_num(va_arg(argument, unsigned int), 'X');
	if (c == 'p')
		result += ft_print_address(va_arg(argument, unsigned long long));
	return (result);
}

int	ft_printf(const char *format, ...)
{
	int		count_print;
	va_list	args_ptr;
	char	*read;

	count_print = 0;
	if (!format)
		return (-1);
	va_start(args_ptr, format);
	read = (char *)format;
	while (*read)
	{
		if (*read == '%' && *(read + 1) != '\0')
		{
			count_print += ft_print_type(args_ptr,*(read + 1));
			read += 2;
		}
		else if (*read == '%' && *(read + 1) == '\0')
			return (va_end(args_ptr), -1);
		else
		{
			count_print += ft_print_char(*read);
			read++;
		}
	}
	return (va_end(args_ptr), count_print);
}
