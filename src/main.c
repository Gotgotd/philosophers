/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:09:19 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/13 17:13:54 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	argument_error(void)
{
	printf("error. program must be runned with at least 4 arguments:\n\
	-number of philosophers\n\
	-time before philosopher dies\n\
	-time each philosopher takes to eat\n\
	-time each philosopher takes to sleep\n\
	and one optional argument : number of time each philopher must eat");
}

int	check_arguments(int ac, char **av)
{
	int	i;
	int	j;

	if (ac > 6 || ac < 5)
			argument_error();
	i = 0;
	while(av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				printf("error. arguments must be digits\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	argument_init(char **av, t_philo *philo)
{
	philo->nb_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->nb_times_to_eat = ft_atoi(av[5]);
	else
		philo->nb_times_to_eat = 0;
	philo->fork = malloc(sizeof(int) * philo->nb_philo);
	return (philo);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (check_arguments(ac, av) == 1)
		return (1);
	philo = malloc(sizeof(t_philo));
	if (!philo)
	{
		printf("error. failed to allocate memory for philo struct");
		return (1);
	}
	argument_init(av, philo);

	
	free(philo->fork);
	free(philo);
	return (0);
}
