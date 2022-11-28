/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:03:19 by tamsi             #+#    #+#             */
/*   Updated: 2022/11/23 18:11:52 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	set_dinner_end(t_dinner *dinner, int set)
{
	pthread_mutex_lock(&dinner->dinner_wait);
	dinner->end = set;
	pthread_mutex_unlock(&dinner->dinner_wait);
}

int	is_dinner_ended(t_dinner *dinner)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&dinner->dinner_mtx);
	if (dinner->end)
		ret = 1;
	pthread_mutex_unlock(&dinner->dinner_mtx);
	return (ret);
}

void	*philo_routine(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (get_current_time() < philo->dinner->start_time)
		continue ;
	while (!is_dinner_ended(philo->dinner))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int		end_eat_cond(t_dinner *dinner)
{
	unsigned int	check_eat_count;
	unsigned int	i;

	i = 0;
	check_eat_count = 1;
	while (i < dinner->nb_philos)
	{
		pthread_mutex_lock(&dinner->dinner_mtx);
		if (dinner->philos[i]->eat_count < dinner->must_eat_count)
			check_eat_count = 0;
		if ((get_current_time() - dinner->philos[i]->last_dinner) >= dinner->time_to_die)
		{
			died(dinner->philos[i]);
			set_dinner_end(dinner, 1);
			pthread_mutex_unlock(&dinner->dinner_mtx);
			return (1);
		}
		pthread_mutex_lock(&dinner->dinner_mtx);
		i++;
	}
	set_dinner_end(dinner, !check_eat_count);
	return (check_eat_count);
}

void	*check_philo_routine(void	*data)
{
	t_dinner		*dinner;

	dinner = (t_dinner *)data;
	while (get_current_time() < dinner->start_time)
		continue ;
	while (1)
	{
		if (end_eat_cond(dinner))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	start_dinner(t_dinner *dinner)
{
	unsigned int	i;

	dinner->start_time = get_current_time() + dinner->nb_philos * 21;
	i = 0;
	while (i < dinner->nb_philos)
	{
		if (pthread_create(&dinner->philos[i]->thread, NULL, &philo_routine, dinner->philos[i]) != 0)
			return (int_error_msg("philo thread creation gone wrong.\n"));
		i++;
	}
	if (pthread_create(&dinner->check_philos, NULL, &check_philo_routine, dinner) != 0)
		return (int_error_msg("checker thread creation gone wrong.\n"));
	return (1);
}

void	end_dinner(t_dinner *dinner)
{
	unsigned int	i;

	i = 0;
	pthread_join(dinner->check_philos, NULL);
	while (i < dinner->nb_philos)
	{
		pthread_join(dinner->philos[i]->thread, NULL);
		i++;
	}
	pthread_mutex_destroy(dinner->forks);
	pthread_mutex_destroy(&dinner->printer);
	pthread_mutex_destroy(&dinner->dinner_mtx);
	pthread_mutex_destroy(&dinner->dinner_wait);
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
