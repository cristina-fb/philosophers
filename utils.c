/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/05 10:17:46 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (str)
	{
		while ((str[i] == '\n') || (str[i] == '\v') || (str[i] == '\f')
			|| (str[i] == '\r') || (str[i] == '\t') || (str[i] == ' '))
			i++;
		if (str[i] == '+')
			i++;
		if ((str[i] >= '0') && (str[i] <= '9'))
		{
			while ((str[i] >= '0') && (str[i] <= '9'))
				n = (n * 10) + str[i++] - 48;
			if ((str[i]) || (n > 2147483647))
				return (-1);
			return (n);
		}
	}
	return (-1);
}

int	ft_isdigit(int c)
{
	return ((c >= '0') && (c <= '9'));
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)malloc(size * count);
	if (ptr)
		memset(ptr, 0, size * count);
	return (ptr);
}

long int	get_time(t_philo *philo)
{
	long int	time;

	gettimeofday(&philo->data->tv, NULL);
	time = (((philo->data->tv.tv_sec * 1000000) + philo->data->tv.tv_usec)
			- ((philo->data->sec * 1000000) + philo->data->usec)) / 1000;
	return (time);
}
