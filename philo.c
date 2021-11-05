/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/05 13:38:07 by crisfern         ###   ########.fr       */
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
	//struct timeval	tv;
	if ((argc < 5) || (argc > 6))
		exit(0);
	if (!valid_args(argc, argv))
		exit(0);
	init_data(&data, argc, argv);
	create_philos(&data);
	i = 0;
	/*while (1)
	{
		if (((((tv.tv_sec * 1000000) + tv.tv_usec) - ((tp[0]->last_eat->tv.tv_sec * 1000000) + tp[0]->last_eat->tv.tv_usec)) / 1000) >= data.t_die)
			pthread_detach(tp[0]);
	}*/
	while (1)
	{
		//comprobar muerte
	}
	return (0);
}