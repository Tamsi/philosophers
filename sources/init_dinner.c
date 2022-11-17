/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:19:30 by tamsi             #+#    #+#             */
/*   Updated: 2022/11/17 18:27:08 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_philo		**init_philo(t_dinner *dinner)
{
	t_philo			**philo;
	unsigned int	i;

	i = 0;
	philo = malloc(dinner->nb_philos * sizeof(t_philo));
	if (!philo)
		return (pointer_error_msg("Error when malloc philo."));
	while (i < dinner->nb_philos)
	{
		philo[i] = malloc(sizeof(t_philo) * 1);
		if (!philo[i])
			return (pointer_error_msg("Error when malloc philo."));
		philo[i]->id = i;
		philo[i]->fork[0] = 0;
		philo[i]->fork[1] = 0;
		i++;
	}
	return (philo);
}

t_dinner	*init_dinner(char **av)
{
	t_dinner	*dinner;

	dinner = malloc(sizeof(t_dinner));
	if (!dinner)
		return (pointer_error_msg("Error when malloc dinner."));
	dinner->start_time = 0;
	dinner->nb_philos = ft_atoi(av[1]);
	dinner->time_to_die = ft_atoi(av[2]);
	dinner->time_to_eat = ft_atoi(av[3]);
	dinner->time_to_sleep = ft_atoi(av[4]);
	dinner->philos = init_philo(dinner);
	return (dinner);
}
