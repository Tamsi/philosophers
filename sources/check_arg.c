/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesson <tbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:21:24 by tamsi             #+#    #+#             */
/*   Updated: 2022/12/02 11:21:38 by tbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_check_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' && ft_strlen(str) > 1)
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_arg(int ac, char **av)
{
	int	i;

	if (ac > 6 || ac < 5)
		return (int_error_msg("usage -> ./philo number_of_philosophers time_to_die time_to_eat\
 time_to_sleep [number_of_times_each_philosopher_must_eat].\n"));
	i = 1;
	while (i < ac)
	{
		if (!ft_check_digit(av[i]))
			return (int_error_msg("Arguments must contains only\
 digits and must be positive integers.\n"));
		if (i == 1 && (ft_atoi(av[i]) < 1 || ft_atoi(av[i]) > MAX_PHILO))
			return (int_error_msg("Bad number of philosophers !\n"));
		i++;
	}
	return (1);
}
