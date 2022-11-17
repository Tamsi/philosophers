/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:03:19 by tamsi             #+#    #+#             */
/*   Updated: 2022/11/17 18:33:30 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*thread_routine()
{
	pthread_t tid;

	tid = pthread_self();
	printf("%sThread [%ld]: Le plus grand ennui c'est d'exister sans vivre.%s\n",
		YELLOW, tid, NC);
	return (NULL);
}

// int	start_dinner(t_dinner *dinner)
// {
// 	int	i;

// 	i = 0;
// 	while (i < dinner->nb_philos)
// 	{
// 		if (pthread_create(&philo[i], NULL, thread_routine, NULL) != 0)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

int	main(int ac, char **av)
{
	t_dinner	*dinner;

	if (!ft_check_arg(ac, av))
		return (0);
	dinner = init_dinner(av);
	free_dinner(dinner);
	return (0);
}
