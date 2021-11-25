/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/25 14:56:10 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->d->mutex[philo->f1]);
	gettimeofday(&philo->tv, NULL);
	pthread_mutex_lock(&philo->d->mutex_w);
	if (!philo->d->end)
		printf("%ld %d has taken a fork\n",
			get_time(philo->d->t_init, philo->tv), philo->id + 1);
	pthread_mutex_unlock(&philo->d->mutex_w);
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->d->mutex[philo->f2]);
	gettimeofday(&philo->tv, NULL);
	pthread_mutex_lock(&philo->d->mutex_w);
	if (!philo->d->end)
	{
		printf("%ld %d has taken a fork\n",
			get_time(philo->d->t_init, philo->tv), philo->id + 1);
		printf("%ld %d is eating\n",
			get_time(philo->d->t_init, philo->tv), philo->id + 1);
	}
	pthread_mutex_unlock(&philo->d->mutex_w);
	philo->d->last_eat[philo->id] = philo->tv;
	philo->d->n_eat[philo->id]--;
	ft_usleep(philo->d->t_eat);
	pthread_mutex_unlock(&philo->d->mutex[philo->f1]);
	pthread_mutex_unlock(&philo->d->mutex[philo->f2]);
}

static void	philo_sleep(t_philo *philo)
{
	gettimeofday(&philo->tv, NULL);
	pthread_mutex_lock(&philo->d->mutex_w);
	if (!philo->d->end)
		printf("%ld %d is sleeping\n",
			get_time(philo->d->t_init, philo->tv), philo->id + 1);
	pthread_mutex_unlock(&philo->d->mutex_w);
	ft_usleep(philo->d->t_sleep);
}

static void	philo_think(t_philo *philo)
{
	gettimeofday(&philo->tv, NULL);
	pthread_mutex_lock(&philo->d->mutex_w);
	if (!philo->d->end)
		printf("%ld %d is thinking\n",
			get_time(philo->d->t_init, philo->tv), philo->id + 1);
	pthread_mutex_unlock(&philo->d->mutex_w);
}

void	*actions(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo)
	{
		while (1)
		{
			if ((philo->id % 2) == 0)
				usleep(100);
			philo_fork(philo);
			philo_eat(philo);
			philo_sleep(philo);
			philo_think(philo);
			if (philo->d->end)
				break ;
		}
		free(philo);
	}
	return (0);
}
