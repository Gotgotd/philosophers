/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:09:19 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/20 17:27:38 by gdaignea         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_data	*data;

	if (check_arguments(ac, av) == 1)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("error. failed to allocate memory for data struct");
		return (1);
	}
	init_data(av, data);
	init_philo(data);
	init_mutex(data);
	create_threads(data);
	is_done_eating_or_dead(data);
	wait_threads(data);
	//destroy_mutex(data);
	free(data->fork);
	free(data);
	return (0);
}
