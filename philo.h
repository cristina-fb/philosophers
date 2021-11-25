/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/25 14:54:11 by crisfern         ###   ########.fr       */
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
	int				end;
	int				n_eat_ini;
	int				*n_eat;
	struct timeval	t_init;
	struct timeval	*last_eat;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mutex_w;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				f1;
	int				f2;
	struct timeval	tv;
	struct timeval	t_init;
	t_data			*d;
}	t_philo;

void		free_callocs(t_data *data);
void		destroy_mutex(t_data *data, int n);
void		ft_usleep(int a);
void		*create_philos(t_data *data);
void		*ft_calloc(size_t count, size_t size);
void		*actions(void *p);
int			ft_atoi(const char *str);
int			init_data(t_data *data, int argc, char **argv);
int			ft_isdigit(int c);
int			all_eat(t_data *data);
long int	get_time(struct timeval tv1, struct timeval tv2);
#endif