/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:09:19 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/26 14:58:10 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	argument_error(void)
{
	printf("error. program must be runned with at least 4 arguments:\n\
-number of datasophers\n\
-time before datasopher dies\n\
-time each datasopher takes to eat\n\
-time each datasopher takes to sleep\n\
and one optional argument : number of time each philosopher must eat");
}

int	check_arguments(int ac, char **av)
{
	int	i;
	int	j;

	if (ac > 6 || ac < 5)
	{
		argument_error();
		return (1);
	}
	i = 1;
	while (av[i])
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

void	hell_is_other_people(t_data *data)
{
	data->start_time = get_current_time();
	ft_display(data->philo, "has taken a fork 🍴");
	usleep(data->time_to_die * 1000);
	ft_display(data->philo, " died 💀");
	free(data->fork);
	free(data->philo);
	free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (check_arguments(ac, av) == 1)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (!init_data(av, data) || !init_philo(data))
		return (1);
	if (data->nb_philo == 1)
	{
		hell_is_other_people(data);
		return (0);
	}
	else if (data->nb_philo == 0)
	{
		printf("error. there must be at least 1 philosopher\n");
		return (1);
	}
	init_mutex(data);
	create_threads(data);
	is_done_eating_or_dead(data);
	wait_threads(data);
	destroy_and_free(data);
	return (0);
}
