/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:29:09 by tbesson           #+#    #+#             */
/*   Updated: 2021/11/24 16:30:49 by tbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*str && (*str == 32 || (*str >= 9 && *str <= 13)))
		str++;
	if ((*str == '-' || *str == '+'))
		if (*(str++) == '-')
			sign = -1;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		result = result * 10 + *str - '0';
		str++;
	}
	result *= sign;
	return (result);
}
