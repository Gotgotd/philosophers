/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:37:04 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/25 17:45:06 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	philo_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		usleep(3000);
		pthread_mutex_lock(philo->left_fork);
	}
	else
		pthread_mutex_lock(philo->right_fork);
	if (!check_stop(philo))
		ft_display(philo, "has taken a fork 🍴");
	if (philo->id % 2 == 0)
	{
		usleep(3000);
		pthread_mutex_lock(philo->right_fork);
	}
	else
		pthread_mutex_lock(philo->left_fork);
	if (!check_stop(philo))
		ft_display(philo, "has taken a fork 🍴");
}

void	philo_eat(t_philo *philo)
{
	philo_take_fork(philo);
	if (check_stop(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(&philo->data->m_start_time);
	philo->start_eating_time = get_time_stamp(philo->data);
	pthread_mutex_unlock(&philo->data->m_start_time);
	ft_display(philo, "is eating 🍚");
	usleep(philo->data->time_to_eat * 1000);
	drop_forks(philo);
	pthread_mutex_lock(&philo->m_nb_meals_eaten);
	if (philo->data->nb_times_to_eat != -1)
	{
		philo->nb_meals_eaten += 1;
	}
	pthread_mutex_unlock(&philo->m_nb_meals_eaten);
}

void	philo_sleep(t_philo *philo)
{
	ft_display(philo, "is sleeping 😴");
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	ft_display(philo, "is thinking 💡");
}
