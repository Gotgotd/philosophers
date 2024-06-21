/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_done_eating_or_dead.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:50:17 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/21 16:05:08 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_if_alive(t_philo *philo)
{
	long int	countdown;
	long int	current_time;

	current_time = get_time_stamp(philo->data);
	countdown = current_time - philo->start_eating_time;
	if (countdown >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->m_stop);
		philo->data->stop = true;
		pthread_mutex_unlock(&philo->data->m_stop);
		pthread_mutex_lock(&philo->data->display);
		ft_display(philo, " died 💀");
		pthread_mutex_unlock(&philo->data->display);
		return;
	}
}

void	check_if_done_eating(t_philo *philo)
{
	if (philo->nb_meals_eaten == philo->data->nb_times_to_eat)
	{
		pthread_mutex_lock(&philo->data->display);
		printf("philo %i is done eating\n", philo->id);
		pthread_mutex_unlock(&philo->data->display);
		philo->done_eating = true;
		philo->data->nb_done_eating += 1;
	}
	if (philo->data->nb_done_eating == philo->data->nb_philo)
	{
		pthread_mutex_lock(&philo->data->display);
		printf("everybody is done\n");
		pthread_mutex_unlock(&philo->data->display);
		pthread_mutex_lock(&philo->data->m_stop);
		philo->data->stop = true;
		pthread_mutex_unlock(&philo->data->m_stop);
	}
}

void	is_done_eating_or_dead(t_data *data)
{
	int	i;

	while (data->stop == false)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			check_if_alive(&data->philo[i]);
			if (data->nb_times_to_eat != -1 && data->philo[i].done_eating == false)
				check_if_done_eating(&data->philo[i]);
			i++; 
		}
	}
}

int	check_stop(t_philo *philo)
{
	if (philo->data->stop == true || philo->done_eating == true)
		return (1);
	else
		return (0);
}