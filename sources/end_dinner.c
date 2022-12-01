/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_dinner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:31:47 by tamsi             #+#    #+#             */
/*   Updated: 2022/12/01 15:12:26 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	end_dinner_cond(t_dinner *dinner)
{
	unsigned int	check_eat_count;
	unsigned int	i;

	i = 0;
	check_eat_count = 1;
	if (dinner->must_eat_count == -1)
		check_eat_count = 0;
	while (i < dinner->nb_philos)
	{
		pthread_mutex_lock(&dinner->eating_mtx);
		if (dinner->philos[i]->eat_count < dinner->must_eat_count)
			check_eat_count = 0;
		if ((get_current_time() - dinner->philos[i]->last_dinner)
			>= dinner->time_to_die)
		{
			died(dinner->philos[i]);
			return (1);
		}
		pthread_mutex_unlock(&dinner->eating_mtx);
		i++;
	}
	set_dinner_end(dinner, check_eat_count);
	return (check_eat_count);
}

void	set_dinner_end(t_dinner *dinner, int set)
{
	pthread_mutex_lock(&dinner->wait);
	dinner->end = set;
	pthread_mutex_unlock(&dinner->wait);
}

int	is_dinner_ended(t_dinner *dinner)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&dinner->wait);
	if (dinner->end)
		ret = 1;
	pthread_mutex_unlock(&dinner->wait);
	return (ret);
}

void	free_dinner(t_dinner *dinner)
{
	unsigned int	i;

	if (!dinner)
		return ;
	i = 0;
	if (dinner->forks)
		free(dinner->forks);
	if (dinner->philos)
	{
		while (i < dinner->nb_philos)
		{
			if (dinner->philos[i] != NULL)
				free(dinner->philos[i]);
			i++;
		}
		free(dinner->philos);
	}
	free(dinner);
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
	pthread_mutex_destroy(&dinner->eating_mtx);
	pthread_mutex_destroy(&dinner->wait);
}
