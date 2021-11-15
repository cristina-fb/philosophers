/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/15 15:17:12 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if ((argc < 5) || (argc > 6))
		return (0);
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

int	all_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (data->ended[i] == 0)
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
		while ((i < data->n_philo) && (!data->ended[i]))
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
		if (all_eat(data))
			break ;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (!valid_args(argc, argv))
	{
		printf("Invalid arguments\n");
		return (0);
	}
	if (!init_data(&data, argc, argv))
		return (0);
	if (!create_philos(&data))
	{
		printf("Error\n");
		return (0);
	}
	death_loop(&data);
	return (0);
}
