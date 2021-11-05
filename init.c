/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/05 10:39:34 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, int argc, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_eat = ft_atoi(argv[5]);
	else
		data->n_eat = -1;
}

static t_philo	*new_philo(t_data *data, int i)
{
	t_philo	*philo;

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
	data->mx = (pthread_mutex_t *)ft_calloc(data->n_philo,
			sizeof(pthread_mutex_t));
	pthread_mutex_init(&data->mx_w, NULL);
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->mx[i], NULL);
		i++;
	}
	gettimeofday(&data->tv, NULL);
	data->sec = data->tv.tv_sec;
	data->usec = data->tv.tv_usec;
	i = 0;
	while (i < data->n_philo)
	{
		pthread_create(&tp[i], NULL, &actions, new_philo(data, i));
		i++;
	}
	return (tp);
}
