/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesson <tbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:52:01 by tamsi             #+#    #+#             */
/*   Updated: 2022/11/28 16:50:36 by tbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	print_states(int states, t_philo *philo)
{
	if (is_dinner_ended(philo->dinner))
		return ;
	pthread_mutex_lock(&philo->dinner->printer);
	if (states == 0)
		printf("%i %i died\n", get_current_time(), philo->id + 1);
	else if (states == 1)
		printf(YELLOW"%i %i has taken fork %i\n"RESET,
			get_current_time(), philo->id + 1, philo->fork[0] + 1);
	else if (states == 2)
		printf(YELLOW"%i %i has taken fork %i\n"RESET,
			get_current_time(), philo->id + 1, philo->fork[1] + 1);
	else if (states == 3)
		printf(RED"%i %i is eating\n"RESET, get_current_time(), philo->id + 1);
	else if (states == 4)
		printf(YELLOW"%i %i is sleeping\n"RESET,
			get_current_time(), philo->id + 1);
	else
		printf(YELLOW"%i %i is thinking\n"RESET,
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
	print_states(DIE, philo);
	pthread_mutex_unlock(&philo->dinner->eating_mtx);
}

void	thinking(t_philo *philo)
{
	time_t	time_to_think;

	time_to_think = (philo->dinner->time_to_die - (get_current_time() - philo->last_dinner) - philo->dinner->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 1;
	if (!is_dinner_ended(philo->dinner))
	{
		pthread_mutex_lock(&philo->dinner->eating_mtx);
		print_states(THINK, philo);
		pthread_mutex_unlock(&philo->dinner->eating_mtx);
		wait_time(time_to_think);
	}
}

void	eating(t_philo *philo)
{
	time_t	time_to_eat;

	time_to_eat = get_current_time() + philo->dinner->time_to_eat;
	pthread_mutex_lock(&philo->dinner->forks[philo->fork[0]]);
	print_states(FORK_1, philo);
	pthread_mutex_lock(&philo->dinner->forks[philo->fork[1]]);
	print_states(FORK_2, philo);
	print_states(EAT, philo);
	pthread_mutex_lock(&philo->dinner->eating_mtx);
	philo->last_dinner = get_current_time();
	pthread_mutex_unlock(&philo->dinner->eating_mtx);
	wait_time(time_to_eat);
	if (!is_dinner_ended(philo->dinner))
	{
		pthread_mutex_lock(&philo->dinner->eating_mtx);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->dinner->eating_mtx);
	}
	pthread_mutex_unlock(&philo->dinner->forks[philo->fork[0]]);
	pthread_mutex_unlock(&philo->dinner->forks[philo->fork[1]]);
}
