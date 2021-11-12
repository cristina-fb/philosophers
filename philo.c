/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/12 16:40:04 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_args(int argc, char **argv)
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

int	death_loop(t_data *data)
{
	int				i;
	struct timeval	tv;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{
			gettimeofday(&tv, NULL);
			if (get_time(data->last_eat[i], tv) > data->t_die)
			{
				pthread_mutex_lock(&data->mutex_w);
				printf("%ld %d died\n", get_time(data->t_init, tv), i + 1);
				pthread_mutex_unlock(&data->mutex_w);
				return (0);
			}
			i++;
		}
	}
	return (0);
}

void	free_data(t_data *data)
{
	if (data->n_eat)
		free(data->n_eat);
	if (data->last_eat)
		free(data->last_eat);
	if (data->mutex)
	{
		pthread_mutex_destroy(&data->mutex[0]);
		free(data->mutex);
	}
	pthread_mutex_destroy(&data->mutex_w);
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (argc < 5)
	{
		printf("Too few arguments\n");
		return (0);
	}
	else if (argc > 6)
	{
		printf("Too much arguments\n");
		return (0);
	}
	if (!valid_args(argc, argv))
	{
		printf("Invalid arguments\n");
		return (0);
	}
	if (!init_data(&data, argc, argv))
	{
		printf("Error\n");
		//free_data(&data);
		return (0);
	}
	if (!create_philos(&data))
	{
		printf("Error\n");
		//free_data(&data);
		return (0);
	}
	death_loop(&data);
	//free_data(&data);
	return (0);
}
