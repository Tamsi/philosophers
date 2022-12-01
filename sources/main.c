/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:03:19 by tamsi             #+#    #+#             */
/*   Updated: 2022/12/01 17:04:50 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philo_routine(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->eating_mtx);
	philo->last_dinner = philo->dinner->start_time;
	pthread_mutex_unlock(&philo->eating_mtx);
	while (get_current_time() < philo->dinner->start_time)
		continue ;
	if (philo->id % 2)
		wait_time(get_current_time() + 1);
	while (!is_dinner_ended(philo->dinner))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	*check_philo_routine(void	*data)
{
	t_dinner	*dinner;

	dinner = (t_dinner *)data;
	while (get_current_time() < dinner->start_time)
		continue ;
	while (1)
	{
		if (end_dinner_cond(dinner))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	start_dinner(t_dinner *dinner)
{
	unsigned int	i;

	dinner->start_time = get_current_time() + (dinner->nb_philos * 25);
	i = 0;
	if (dinner->must_eat_count == 0)
		return (1);
	if (dinner->nb_philos == 1)
	{
		printf("%lu : 1 has taken fork 1\n", get_current_time());
		wait_time(get_current_time() + dinner->time_to_die);
		printf(RED"%lu : 1 died\n"RESET, get_current_time());
		return (1);
	}
	while (i < dinner->nb_philos)
	{
		if (pthread_create(&dinner->philos[i]->thread,
				NULL, &philo_routine, dinner->philos[i]) != 0)
			return (int_error_msg("philo thread creation gone wrong.\n"));
		i++;
	}
	if (pthread_create(&dinner->check_philos,
			NULL, &check_philo_routine, dinner) != 0)
		return (int_error_msg("checker thread creation gone wrong.\n"));
	return (1);
}

int	main(int ac, char **av)
{
	t_dinner	*dinner;

	if (!ft_check_arg(ac, av))
		return (0);
	dinner = init_dinner(av);
	start_dinner(dinner);
	end_dinner(dinner);
	free_dinner(dinner);
	return (0);
}
