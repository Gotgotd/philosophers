/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:37:04 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/25 17:46:23 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!check_stop(philo))
	{
		philo_eat(philo);
		if (check_stop(philo))
			return (NULL);
		philo_sleep(philo);
		if (check_stop(philo))
			return (NULL);
		philo_think(philo);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i].tid, NULL, philo_routine,
			&data->philo[i]);
		i++;
	}
}

void	wait_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].tid, NULL);
		i++;
	}
}
