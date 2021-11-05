/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/05 17:07:26 by crisfern         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_data			data;
	int				i;
	struct timeval	tv;
	pthread_t		*tp;
	
	if ((argc < 5) || (argc > 6))
		exit(0);
	if (!valid_args(argc, argv))
		exit(0);
	init_data(&data, argc, argv);
	tp = create_philos(&data);
	while (1)
	{
		i = 0;
		while (i < data.n_philo)
		{
			gettimeofday(&tv, NULL);
			if (get_time(data.last_eat[i], tv) >= data.t_die)
			{
				pthread_detach(tp[i]);
				pthread_mutex_lock(&data.mutex_w);
				printf("%ld %d died\n", get_time(data.last_eat[i], tv), i);
				pthread_mutex_unlock(&data.mutex_w);
				exit(0);
			}
			i++;
		}
	}
	return (0);
}
