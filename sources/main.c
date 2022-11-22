/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:03:19 by tamsi             #+#    #+#             */
/*   Updated: 2022/11/21 17:04:13 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philo_routine(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	eating(philo);
	sleeping(philo);
	thinking(philo);
	return (data);
}

int	start_dinner(t_dinner *dinner)
{
	unsigned int	i;

	dinner->start_time = get_current_time() + dinner->nb_philos * 20;
	i = 0;
	while (i < dinner->nb_philos)
	{
		if (pthread_create(&dinner->philos[i]->thread, NULL, &philo_routine, dinner->philos[i]) != 0)
			return (int_error_msg("philo thread creation gone wrong.\n"));
		i++;
	}
	return (1);
}

void	end_dinner(t_dinner *dinner)
{
	unsigned int	i;

	i = 0;
	while (i < dinner->nb_philos)
	{
		pthread_join(dinner->philos[i]->thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_dinner	*dinner;

	if (!ft_check_arg(ac, av))
		return (0);
	dinner = init_dinner(av);
	// while (1)
	start_dinner(dinner);
	end_dinner(dinner);
	free_dinner(dinner);
	return (0);
}
