/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/25 14:45:35 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_mutex_destroy(&data->mutex[i++]);
	if (n == data->n_philo)
		pthread_mutex_destroy(&data->mutex_w);
}

void	free_callocs(t_data *data)
{
	if (data->n_eat)
		free(data->n_eat);
	if (data->last_eat)
		free(data->last_eat);
	if (data->mutex)
		free(data->mutex);
}

int	all_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (data->n_eat[i] > 0)
			return (0);
		i++;
	}
	data->end = 1;
	return (1);
}
