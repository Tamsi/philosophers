/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesson <tbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:19:30 by tamsi             #+#    #+#             */
/*   Updated: 2022/11/28 16:50:22 by tbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

pthread_mutex_t	*init_forks_mutex(t_dinner *dinner)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * (dinner->nb_philos + 1));
	if (!forks)
		pointer_error_msg("malloc forks mutex gone wrong.\n");
	i = 0;
	while (i < dinner->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			pointer_error_msg("init forks mutex gone wrong.\n");
		i++;
	}
	return (forks);
}

static t_philo	**init_philo(t_dinner *dinner)
{
	t_philo			**philo;
	unsigned int	i;

	i = 0;
	philo = malloc(dinner->nb_philos * sizeof(t_philo));
	if (!philo)
		return (pointer_error_msg("Error when malloc philo."));
	while (i < dinner->nb_philos)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (pointer_error_msg("Error when malloc philo."));
		philo[i]->dinner = dinner;
		philo[i]->last_dinner = 0;
		philo[i]->id = i;
		philo[i]->fork[(i + 1) % 2] = philo[i]->id;
		philo[i]->fork[i % 2] = (philo[i]->id + 1) % dinner->nb_philos;
		philo[i]->eat_count = 0;
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
	if (pthread_mutex_init(&dinner->printer, 0) != 0
		|| pthread_mutex_init(&dinner->eating_mtx, 0) != 0
		|| pthread_mutex_init(&dinner->wait, 0) != 0)
		pointer_error_msg("init mutex gone wrong.\n");
	dinner->start_time = 0;
	dinner->nb_philos = ft_atoi(av[1]);
	dinner->time_to_die = ft_atoi(av[2]);
	dinner->time_to_eat = ft_atoi(av[3]);
	dinner->time_to_sleep = ft_atoi(av[4]);
	dinner->end = 0;
	dinner->must_eat_count = -1;
	if (av[5])
		dinner->must_eat_count = ft_atoi(av[5]);
	dinner->philos = init_philo(dinner);
	dinner->forks = init_forks_mutex(dinner);
	return (dinner);
}
