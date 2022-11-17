/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:39:38 by tbesson           #+#    #+#             */
/*   Updated: 2021/11/26 17:04:15 by tbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	control_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(base) <= 1)
		return (0);
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		j = -1;
		while (base[++j])
			if (base[i] == base[j] && j != i)
				return (0);
		i++;
	}
	return (1);
}

int	ft_putnbr_unsigned(unsigned long long int nb, char *base)
{
	int				count;
	unsigned int	base_len;

	count = 0;
	base_len = ft_strlen(base);
	if (control_base(base) == 0)
		return (0);
	if (nb > base_len - 1)
		count += ft_putnbr_unsigned(nb / base_len, base);
	ft_putchar(base[nb % base_len]);
	count++;
	return (count);
}
