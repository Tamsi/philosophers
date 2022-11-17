/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesson <tbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 19:18:26 by tbesson           #+#    #+#             */
/*   Updated: 2022/01/28 17:48:49 by tbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_args(char c, va_list args)
{
	int	i;

	i = 0;
	if (c == 'c')
		i += ft_printchar(args);
	else if (c == 's')
		i += ft_printstr(args);
	else if (c == 'p')
		i += ft_printpointer(args);
	else if (c == 'd' || c == 'i')
		i += ft_printinteger(args);
	else if (c == 'u')
		i += ft_printunsigned(args);
	else if (c == 'x')
		i += ft_printhexa_lower(args);
	else if (c == 'X')
		i += ft_printhexa_upper(args);
	else if (c == '%')
		i += write(1, "%", 1);
	return (i);
}

int	parse_s(const char *s, va_list args)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '%')
			count += handle_args(s[++i], args);
		else
		{
			ft_putchar(s[i]);
			count++;
		}
		i++;
	}
	return (count);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;

	va_start(args, s);
	return (parse_s(s, args));
}
