/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/22 13:41:09 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leaks(void)
{
	system("leaks philo");
}

static int	valid_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if ((argc < 5) || (argc > 6))
	{
		printf("Invalid number of arguments\n");
		return (0);
	}
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 1)
		{
			printf("Invalid arguments\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	death_loop(t_data *data, int i, long int time)
{
	struct timeval	tv;

	while (1)
	{
		i = -1;
		while ((++i < data->n_philo))
		{
			gettimeofday(&tv, NULL);
			if (data->n_eat[i] == 0)
				time = get_time(data->t_init, tv);
			else
				time = get_time(data->last_eat[i], tv);
			if (time > data->t_die)
			{
				pthread_mutex_lock(&data->mutex_w);
				printf("%ld %d died\n", get_time(data->t_init, tv), i + 1);
				data->end = 1;
				pthread_mutex_unlock(&data->mutex_w);
				return (0);
			}
		}
		if (all_eat(data))
			break ;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;
	pthread_t		*tp;
	int				i;

	atexit(leaks);
	i = 0;
	if (!valid_args(argc, argv))
		return (0);
	if (!init_data(&data, argc, argv))
	{
		printf("Error\n");
		return (0);
	}
	tp = create_philos(&data);
	if (tp)
	{
		death_loop(&data, 0, 0);
		if (data.n_philo > 1)
			while (i < data.n_philo)
				pthread_join(tp[i++], NULL);
		free(tp);
	}
	destroy_mutex(&data, data.n_philo);
	free_callocs(&data);
	return (0);
}
