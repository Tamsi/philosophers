/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:27:00 by tamsi             #+#    #+#             */
/*   Updated: 2022/11/20 13:20:17 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_current_time()
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return (tval.tv_usec);
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
