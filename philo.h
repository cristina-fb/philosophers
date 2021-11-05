/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/05 10:39:54 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_data
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				*fork;
	long int		sec;
	long int		usec;
	struct timeval	tv;
	pthread_mutex_t	*mx;
	pthread_mutex_t	mx_w;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				f1;
	int				f2;
	struct timeval	last_eat;
	t_data			*data;
}	t_philo;

int			ft_isdigit(int c);
int			ft_atoi(const char *str);
long int	get_time(t_philo *philo);
void		init_data(t_data *data, int argc, char **argv);
void		*actions(void *p);
void		*ft_calloc(size_t count, size_t size);
pthread_t	*create_philos(t_data *data);
#endif