/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/10/29 10:17:29 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

typedef struct s_philo
{
	int	id;
	int	n_eat;
	int	fork_r;
	int	fork_l;
}	t_philo;

typedef struct s_data
{
	int		n_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_eat;
	t_philo	**list;
}	t_data;

void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
#endif