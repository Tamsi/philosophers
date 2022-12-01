/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:52:01 by tamsi             #+#    #+#             */
/*   Updated: 2022/12/01 17:05:15 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	print_states(int states, t_philo *philo)
{
	if (is_dinner_ended(philo->dinner))
		return ;
	pthread_mutex_lock(&philo->dinner->printer);
	if (states == 0)
		printf(RED"%lu : %i died\n"RESET, get_current_time(), philo->id + 1);
	else if (states == 1)
		printf("%lu : %i has taken fork %i\n",
			get_current_time(), philo->id + 1, philo->fork[0] + 1);
	else if (states == 2)
		printf("%lu : %i has taken fork %i\n",
			get_current_time(), philo->id + 1, philo->fork[1] + 1);
	else if (states == 3)
		printf("%lu : %i is eating\n", get_current_time(), philo->id + 1);
	else if (states == 4)
		printf("%lu : %i is sleeping\n",
			get_current_time(), philo->id + 1);
	else
		printf("%lu : %i is thinking\n",
			get_current_time(), philo->id + 1);
	pthread_mutex_unlock(&philo->dinner->printer);
}

void	sleeping(t_philo *philo)
{
	time_t	time_to_wakeup;

	if (!is_dinner_ended(philo->dinner))
	{
		time_to_wakeup = get_current_time() + philo->dinner->time_to_sleep;
		print_states(SLEEP, philo);
		wait_time(time_to_wakeup);
	}
}

void	died(t_philo *philo)
{
	set_dinner_end(philo->dinner, 1);
	printf(RED"%lu : %i died\n"RESET, get_current_time(), philo->id + 1);
	pthread_mutex_unlock(&philo->eating_mtx);
}

void	thinking(t_philo *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->eating_mtx);
	time_to_think = (philo->dinner->time_to_die
			- (get_current_time() - philo->last_dinner)
			- philo->dinner->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->eating_mtx);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 600)
		time_to_think = 200;
	if (!is_dinner_ended(philo->dinner))
	{
		pthread_mutex_lock(&philo->eating_mtx);
		print_states(THINK, philo);
		pthread_mutex_unlock(&philo->eating_mtx);
		wait_time(get_current_time() + time_to_think);
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->forks[philo->fork[0]]);
	print_states(FORK_1, philo);
	pthread_mutex_lock(&philo->dinner->forks[philo->fork[1]]);
	print_states(FORK_2, philo);
	print_states(EAT, philo);
	pthread_mutex_lock(&philo->eating_mtx);
	philo->last_dinner = get_current_time();
	pthread_mutex_unlock(&philo->eating_mtx);
	wait_time(get_current_time() + philo->dinner->time_to_eat);
	if (!is_dinner_ended(philo->dinner))
	{
		pthread_mutex_lock(&philo->eating_mtx);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->eating_mtx);
	}
	pthread_mutex_unlock(&philo->dinner->forks[philo->fork[0]]);
	pthread_mutex_unlock(&philo->dinner->forks[philo->fork[1]]);
}
