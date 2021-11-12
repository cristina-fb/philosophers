/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/12 10:54:17 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data_2(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (argc == 6)
			data->n_eat[i] = ft_atoi(argv[5]);
		else
			data->n_eat[i] = -1;
		if (pthread_mutex_init(&data->mutex[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->mutex_w, NULL))
		return (0);
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->n_eat = (int *)ft_calloc(data->n_philo, sizeof(int));
	data->last_eat = (struct timeval *)ft_calloc(data->n_philo,
			sizeof(struct timeval));
	data->mutex = (pthread_mutex_t *)ft_calloc(data->n_philo,
			sizeof(pthread_mutex_t));
	if (data->n_eat && data->last_eat && data->mutex)
	{
		if (!init_data_2(data, argc, argv))
			return (0);
	}
	else
		return (0);
	return (1);
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

	i = 0;
	tp = (pthread_t *)ft_calloc(data->n_philo, sizeof(pthread_t));
	if (tp)
	{
		gettimeofday(&data->t_init, NULL);
		while (i < data->n_philo)
		{
			data->last_eat[i] = data->t_init;
			if (pthread_create(&tp[i], NULL, &actions, new_philo(data, i)))
				return (0);
			i++;
		}
	}
	return (tp);
}
