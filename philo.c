/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/03 16:42:43 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	valid_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!argv[i])
			return (0);
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

/*void	ft_sleep(int t)
{
	t = t * 1000;
	while (t-- > 0)
		usleep(1);
}*/

long int	get_time(t_philo *philo)
{
	long int	time;

	gettimeofday(&philo->data->tv, NULL);
	time = (((philo->data->tv.tv_sec * 1000000) + philo->data->tv.tv_usec)
			- ((philo->data->sec * 1000000) + philo->data->usec)) / 1000;
	return (time);
}

void	*function(void *p)
{
	t_philo			*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(&philo->data->mx[philo->f1]);
	pthread_mutex_lock(&philo->data->mx_w);
	printf("%ld %d has taken a fork\n", get_time(philo), philo->id);
	pthread_mutex_unlock(&philo->data->mx_w);
	pthread_mutex_lock(&philo->data->mx[philo->f2]);
	pthread_mutex_lock(&philo->data->mx_w);
	printf("%ld %d has taken a fork\n", get_time(philo), philo->id);
	printf("%ld %d is eating\n", get_time(philo), philo->id);
	pthread_mutex_unlock(&philo->data->mx_w);
	usleep(philo->data->t_eat * 1000);
	pthread_mutex_unlock(&philo->data->mx[philo->f1]);
	pthread_mutex_unlock(&philo->data->mx[philo->f2]);
	pthread_mutex_lock(&philo->data->mx_w);
	printf("%ld %d is sleeping\n", get_time(philo), philo->id);
	pthread_mutex_unlock(&philo->data->mx_w);
	usleep(philo->data->t_sleep * 1000);
	pthread_mutex_lock(&philo->data->mx_w);
	printf("%ld %d is thinking\n", get_time(philo), philo->id);
	pthread_mutex_unlock(&philo->data->mx_w);
	return (0);
}

t_philo	*new_philo(t_data *data, int i)
{
	t_philo			*philo;

	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (philo)
	{
		philo->id = i;
		philo->data = data;
		if (i % 2)
		{
			if (i == data->n_philo - 1)
				philo->f2 = 0;
			else
				philo->f2 = i + 1;
			philo->f1 = i;
		}
		else
		{
			if (i == data->n_philo - 1)
				philo->f1 = 0;
			else
				philo->f1 = i + 1;
			philo->f2 = i;
		}
	}
	return (philo);
}

pthread_t	*create_philos(t_data *data)
{
	int				i;
	pthread_t		*tp;

	i = 0;
	tp = (pthread_t *)ft_calloc(data->n_philo, sizeof(pthread_t));
	data->fork = (int *)ft_calloc(data->n_philo, sizeof(int));
	data->mx = (pthread_mutex_t *)ft_calloc(data->n_philo, sizeof(pthread_mutex_t));
	pthread_mutex_init(&data->mx_w, NULL);
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->mx[i], NULL);
		i++;
	}
	i = 0;
	gettimeofday(&data->tv, NULL);
	data->sec = data->tv.tv_sec;
	data->usec = data->tv.tv_usec;
	while (i < data->n_philo)
	{
		pthread_create(&tp[i], NULL, &function, new_philo(data, i));
		i++;
	}
	return (tp);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*tp;
	int			i;

	i = 0;
	if ((argc < 5) || (argc > 6))
		exit(0);
	if (!valid_args(argc, argv))
		exit(0);
	data.n_philo = ft_atoi(argv[1]);
	data.t_die = ft_atoi(argv[2]);
	data.t_eat = ft_atoi(argv[3]);
	data.t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.n_eat = ft_atoi(argv[5]);
	else
		data.n_eat = -1;
	tp = create_philos(&data);
	while (i < data.n_philo)
	{
		pthread_join(tp[i], NULL);
		i++;
	}
	return (0);
}
