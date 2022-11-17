/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_numbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:47:25 by tbesson           #+#    #+#             */
/*   Updated: 2022/08/27 22:17:44 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printinteger(va_list args)
{
	int	nb;

	nb = va_arg(args, int);
	ft_putnbr(nb);
	return (ft_nblen(nb));
}

int	ft_printunsigned(va_list args)
{
	unsigned int	nb;

	nb = va_arg(args, unsigned int);
	ft_putnbr_unsigned((unsigned long long)nb, "0123456789");
	return (ft_unsignedlen(nb));
}
