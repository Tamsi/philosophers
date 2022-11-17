/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:39:10 by tamsi             #+#    #+#             */
/*   Updated: 2022/11/17 18:32:20 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include "libft.h"

# define NC	"\e[0m"
# define RED	"\e[31m"
# define YELLOW	"\e[1;33m"
# define MAX_PHILO	255

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		fork[2];
	time_t				last_meal;
}	t_philo;

typedef struct s_dinner
{
	time_t			start_time;
	unsigned int	nb_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	t_philo			**philos;
}	t_dinner;

int			ft_check_arg(int ac, char **av);
int			int_error_msg(char *str);
void		free_dinner(t_dinner *dinner);
void		*pointer_error_msg(char *str);
t_dinner	*init_dinner(char **av);

#endif
