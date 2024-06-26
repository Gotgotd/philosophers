/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:28:57 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/26 14:58:10 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_and_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
	pthread_mutex_destroy(&data->m_nb_done_eating);
	pthread_mutex_destroy(&data->m_start_time);
	pthread_mutex_destroy(&data->m_stop);
	pthread_mutex_destroy(&data->philo->m_nb_meals_eaten);
	free(data->philo);
	free(data);
}
