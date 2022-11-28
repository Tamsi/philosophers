/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:52:01 by tamsi             #+#    #+#             */
/*   Updated: 2022/11/23 18:10:34 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	print_states(int states, t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->printer);
	if (states == 0)
		printf("%i %i died\n", get_current_time(), philo->id);
	else if (states == 1)
		printf(YELLOW"%i %i has taken fork %i\n"RESET, get_current_time(), philo->id, philo->fork[0] + 1);
	else if (states == 2)
		printf(YELLOW"%i %i has taken fork %i\n"RESET, get_current_time(), philo->id, philo->fork[1] + 1);
	else if (states == 3)
		printf(YELLOW"%i %i is eating\n"RESET, get_current_time(), philo->id);
	else if (states == 4)
		printf(YELLOW"%i %i is sleeping\n"RESET, get_current_time(), philo->id);
	else
		printf(YELLOW"%i %i is thinking\n"RESET, get_current_time(), philo->id);
	pthread_mutex_unlock(&philo->dinner->printer);
}

void	sleeping(t_philo *philo)
{
	time_t	time_to_wakeup;

	time_to_wakeup = get_current_time() + philo->dinner->time_to_sleep;
	print_states(SLEEP, philo);
	while (get_current_time() < time_to_wakeup)
		usleep(100);
}

void	died(t_philo *philo)
{
	print_states(DIE, philo);
}

void	thinking(t_philo *philo)
{
	print_states(THINK, philo);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->dinner_mtx);
	pthread_mutex_lock(&philo->dinner->forks[philo->fork[0]]);
	print_states(FORK_1, philo);
	pthread_mutex_lock(&philo->dinner->forks[philo->fork[1]]);
	print_states(FORK_2, philo);
	print_states(EAT, philo);
	philo->eat_count++;
	philo->last_dinner = get_current_time();
	pthread_mutex_unlock(&philo->dinner->forks[philo->fork[0]]);
	pthread_mutex_unlock(&philo->dinner->forks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->dinner->dinner_mtx);
}
