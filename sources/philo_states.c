/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:52:01 by tamsi             #+#    #+#             */
/*   Updated: 2022/12/02 09:24:31 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	print_states(int states, t_philo *philo)
{
	if (is_dinner_ended(philo->dinner) && states != 0)
		return ;
	pthread_mutex_lock(&philo->dinner->printer);
	ft_putnbr((long long int)(get_current_time() - philo->dinner->start_time));
	write(1, " ", 1);
	ft_putnbr((long long int)philo->id + 1);
	if (states == 0)
		write(1, " died\n", ft_strlen(" died\n"));
	else if (states == 1)
		write(1, " has taken a fork\n", ft_strlen(" has taken a fork\n"));
	else if (states == 2)
		write(1, " has taken a fork\n", ft_strlen(" has taken a fork\n"));
	else if (states == 3)
		write(1, " is eating\n", ft_strlen(" is eating\n"));
	else if (states == 4)
		write(1, " is sleeping\n", ft_strlen(" is sleeping\n"));
	else
		write(1, " is thinking\n", ft_strlen(" is thinking\n"));
	pthread_mutex_unlock(&philo->dinner->printer);
}

void	sleeping(t_philo *philo)
{
	time_t	time_to_wakeup;

	if (!is_dinner_ended(philo->dinner))
	{
		time_to_wakeup = get_current_time() + philo->dinner->time_to_sleep;
		print_states(SLEEP, philo);
		wait_time(philo->dinner, time_to_wakeup);
	}
}

void	died(t_philo *philo)
{
	set_dinner_end(philo->dinner, 1);
	print_states(DIE, philo);
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
		wait_time(philo->dinner, get_current_time() + time_to_think);
	}
}

void	eating(t_philo *philo)
{
	if (is_dinner_ended(philo->dinner))
		return ;
	pthread_mutex_lock(&philo->dinner->forks[philo->fork[0]]);
	print_states(FORK_1, philo);
	pthread_mutex_lock(&philo->dinner->forks[philo->fork[1]]);
	print_states(FORK_2, philo);
	print_states(EAT, philo);
	pthread_mutex_lock(&philo->eating_mtx);
	philo->last_dinner = get_current_time();
	pthread_mutex_unlock(&philo->eating_mtx);
	wait_time(philo->dinner, get_current_time() + philo->dinner->time_to_eat);
	if (!is_dinner_ended(philo->dinner))
	{
		pthread_mutex_lock(&philo->eating_mtx);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->eating_mtx);
	}
	pthread_mutex_unlock(&philo->dinner->forks[philo->fork[0]]);
	pthread_mutex_unlock(&philo->dinner->forks[philo->fork[1]]);
}
