/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:31:47 by tamsi             #+#    #+#             */
/*   Updated: 2022/11/23 17:32:30 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
