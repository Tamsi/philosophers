/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesson <tbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 20:44:02 by tbesson           #+#    #+#             */
/*   Updated: 2021/12/03 12:14:43 by tbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_rev_tab(char *tab, int size)
{
	int	i;
	int	swap;

	i = 0;
	while (i < size / 2)
	{
		swap = tab[size - 1 - i];
		tab[size - i - 1] = tab[i];
		tab[i] = swap;
		i++;
	}
}

static int	ft_numsize(long int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		size++;
	}
	while (n)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	i;
	long int	num;

	num = n;
	str = malloc(sizeof(char) * (ft_numsize(num) + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (num < 0)
		num = -num;
	if (num == 0)
		str[i++] = num % 10 + 48;
	while (num)
	{
		str[i++] = num % 10 + 48;
		num = num / 10;
	}
	if (n < 0)
		str[i++] = '-';
	ft_rev_tab(str, i);
	str[i] = '\0';
	return (str);
}
