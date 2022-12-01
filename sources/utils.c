/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:27:00 by tamsi             #+#    #+#             */
/*   Updated: 2022/12/01 21:16:43 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

time_t	get_current_time(void)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return ((tval.tv_sec * 1000) + (tval.tv_usec / 1000));
}

void	wait_time(time_t time)
{
	while (get_current_time() < time)
		usleep(1000);
}

int	int_error_msg(char *str)
{
	printf(RED"Error: %s"RESET, str);
	return (0);
}

void	*pointer_error_msg(char *str)
{
	printf(RED"Error: %s"RESET, str);
	return (NULL);
}
