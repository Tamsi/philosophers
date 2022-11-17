/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:27:00 by tamsi             #+#    #+#             */
/*   Updated: 2022/11/17 18:18:32 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	int_error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	return (0);
}

void	*pointer_error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	return (NULL);
}
