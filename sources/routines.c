/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:52:06 by tamsi             #+#    #+#             */
/*   Updated: 2022/12/01 22:45:53 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->eating_mtx);
	philo->last_dinner = philo->dinner->start_time;
	pthread_mutex_unlock(&philo->eating_mtx);
	if (philo->id % 2)
		usleep(philo->dinner->time_to_eat * 1000);
	while (!is_dinner_ended(philo->dinner))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	*check_philo_routine(void *data)
{
	t_dinner	*dinner;

	dinner = (t_dinner *)data;
	usleep(dinner->time_to_die * 1000);
	while (1)
	{
		if (end_dinner_cond(dinner))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
