/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/05 15:58:11 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	data->n_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->n_eat = (int *)ft_calloc(data->n_philo, sizeof(int));
	i = 0;
	if (argc == 6)
		while (i < data->n_philo)
			data->n_eat[i++] = ft_atoi(argv[5]);
	else
		while (i < data->n_philo)
			data->n_eat[i++] = -1;
	data->last_eat = (long int *)ft_calloc(data->n_philo, sizeof(long int));
	data->mutex = (pthread_mutex_t *)ft_calloc(data->n_philo,
			sizeof(pthread_mutex_t));
	i = 0;
	while (i < data->n_philo)
		pthread_mutex_init(&data->mutex[i++], NULL);
	pthread_mutex_init(&data->mutex_w, NULL);
}

static t_philo	*new_philo(t_data *data, int i)
{
	t_philo	*philo;

	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (philo)
	{
		philo->id = i;
		philo->d = data;
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

void	*create_philos(t_data *data)
{
	int				i;
	pthread_t		*tp;

	tp = (pthread_t *)ft_calloc(data->n_philo, sizeof(pthread_t));
	gettimeofday(&data->tv, NULL);
	data->t_init = (((data->tv.tv_sec) * 1000000) + data->tv.tv_usec);
	i = 0;
	while (i < data->n_philo)
		data->last_eat[i++] = data->t_init;
	i = 0;
	while (i < data->n_philo)
	{
		pthread_create(&tp[i], NULL, &actions, new_philo(data, i));
		i++;
	}
	return (tp);
}
