/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_hexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:44:29 by tbesson           #+#    #+#             */
/*   Updated: 2022/08/27 22:17:44 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printpointer(va_list args)
{
	void	*ptr;
	int		count;

	ptr = va_arg(args, void *);
	write(1, "0x", 2);
	count = 2;
	count += ft_putnbr_unsigned((unsigned long long)ptr, "0123456789abcdef");
	return (count);
}

int	ft_printhexa_lower(va_list args)
{
	unsigned int	hexa;
	int				count;

	hexa = va_arg(args, unsigned int);
	count = 0;
	count += ft_putnbr_unsigned((unsigned long long)hexa, "0123456789abcdef");
	return (count);
}

int	ft_printhexa_upper(va_list args)
{
	unsigned int	hexa;
	int				count;

	hexa = va_arg(args, unsigned int);
	count = 0;
	count += ft_putnbr_unsigned((unsigned long long)hexa, "0123456789ABCDEF");
	return (count);
}
