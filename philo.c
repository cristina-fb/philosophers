/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/10/29 10:32:21 by crisfern         ###   ########.fr       */
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

t_philo	*new_philo(t_data *data, int i)
{
	t_philo	*philo;

	philo = (t_philo *)ft_calloc(1, sizeof(t_philo *));
	if (philo)
	{
		philo->id = i;
		philo->n_eat = data->n_eat;
		philo->fork_r = 0;
		philo->fork_l = 0;
	}
	return (philo);
}

void	create_philos(t_data *data)
{
	int	i;

	i = 0;
	data->list = ft_calloc(data->n_philo + 1, sizeof(t_philo *));
	if (data->list)
	{
		while (i < data->n_philo)
		{
			data->list[i] = new_philo(data, i);
			i++;
		}
		data->list[i] = 0;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

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
	create_philos(&data);
	return (0);
}
