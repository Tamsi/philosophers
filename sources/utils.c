/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesson <tbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:27:00 by tamsi             #+#    #+#             */
/*   Updated: 2022/11/28 15:31:11 by tbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_current_time(void)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return (tval.tv_usec);
}

void	wait_time(time_t time)
{
	while (get_current_time() < time)
		usleep(100);
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
