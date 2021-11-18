/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/18 16:50:20 by crisfern         ###   ########.fr       */
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
	int				*n_eat;
	int				end;
	int				all;
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
	t_data			*d;
}	t_philo;

int			ft_isdigit(int c);
int			ft_atoi(const char *str);
long int	get_time(struct timeval tv1, struct timeval tv2);
int			init_data(t_data *data, int argc, char **argv);
void		*actions(void *p);
void		*ft_calloc(size_t count, size_t size);
void		*create_philos(t_data *data);
void		ft_usleep(int a);
void		destroy_mutex(t_data *data, int n);
void		free_callocs(t_data *data);
#endif