/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:39:10 by tamsi             #+#    #+#             */
/*   Updated: 2022/11/21 17:05:39 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define RED	"\e[31m"
# define YELLOW	"\e[1;33m"
# define RESET	"\033[0m"
# define MAX_PHILO	255
# define FORK_1	1
# define FORK_2	2
# define EAT	3
# define SLEEP	4
# define THINK	5

typedef struct s_dinner	t_dinner;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	fork[2];
	unsigned int	id;
	unsigned int	eat_count;
	time_t			last_dinner;
	t_dinner		*dinner;
}	t_philo;

typedef struct s_dinner
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	printer;
	pthread_mutex_t	dinner_mtx;
	unsigned int	nb_philos;
	unsigned int	must_eat_count;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	t_philo			**philos;
}	t_dinner;

int			ft_check_arg(int ac, char **av);
int			int_error_msg(char *str);
int			ft_isdigit(int c);
int			ft_atoi(const char *nptr);
int			get_current_time();
void		free_dinner(t_dinner *dinner);
void		*pointer_error_msg(char *str);
void		sleeping(t_philo *philo);
void		eating(t_philo *philo);
void		thinking(t_philo *philo);
t_dinner	*init_dinner(char **av);

#endif
