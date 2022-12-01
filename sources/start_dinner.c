/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:49:34 by tamsi             #+#    #+#             */
/*   Updated: 2022/12/01 23:20:00 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	start_philos(t_dinner *dinner)
{
	unsigned int	i;

	i = 0;
	while (i < dinner->nb_philos)
	{
		if (pthread_create(&dinner->philos[i]->thread,
				NULL, &philo_routine, dinner->philos[i]) != 0)
			return (int_error_msg("philo thread creation gone wrong.\n"));
		i += 1;
	}
	return (1);
}

int	start_dinner(t_dinner *dinner)
{

	dinner->start_time = get_current_time() + (dinner->nb_philos / 2);
	if (dinner->must_eat_count == 0)
		return (1);
	if (dinner->nb_philos == 1 || dinner->time_to_die == 0)
	{
		printf("0 : 1 has taken fork 1\n");
		wait_time(get_current_time() + dinner->time_to_die);
		printf("%lu : 1 died\n", dinner->time_to_die);
		return (1);
	}
	if (!start_philos(dinner))
		return (0);
	if (pthread_create(&dinner->check_philos,
			NULL, &check_philo_routine, dinner) != 0)
		return (int_error_msg("checker thread creation gone wrong.\n"));
	return (1);
}
