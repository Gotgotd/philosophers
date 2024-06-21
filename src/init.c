/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:18:04 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/21 15:05:50 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_data(char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		data->nb_times_to_eat = ft_atoi(av[5]);
		if (data->nb_times_to_eat < 0)
			return ;
	}
	else
		data->nb_times_to_eat = -1;
	data->nb_done_eating = 0;
	pthread_mutex_init(&data->display, NULL);
	pthread_mutex_init(&data->m_stop, NULL);
	data->fork = malloc(sizeof(int) * data->nb_philo);
	if (!data->fork)
		return ;
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
	{
		printf("error initializing philo structure");
		return ;
	}
	while (i < data->nb_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].time_stamp = 0;
		data->philo[i].nb_meals_eaten = 0;
		data->philo[i].left_fork = &data->fork[i];
		data->philo[i].right_fork = &data->fork[(i + 1) % data->nb_philo];
		i++;
	}
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data)
		return ;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
}