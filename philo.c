/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/01 15:48:36 by crisfern         ###   ########.fr       */
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

void	*function(void *p)
{
	t_philo	*philo;
	
	philo = (t_philo *)p;
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
