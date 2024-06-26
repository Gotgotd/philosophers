/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:05:07 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/26 14:58:10 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo
{
	pthread_t		tid;
	int				id;
	long int		time_stamp;
	long int		start_eating_time;
	int				nb_meals_eaten;
	bool			done_eating;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	m_nb_meals_eaten;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times_to_eat;
	int				nb_done_eating;
	long int		start_time;
	bool			stop;
	pthread_mutex_t	display;
	pthread_mutex_t	*fork;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_nb_done_eating;
	pthread_mutex_t	m_start_time;
	t_philo			*philo;
}	t_data;

/* INIT */
int			init_data(char **av, t_data *data);
int			init_philo(t_data *data);
void		init_mutex(t_data *data);

/* IS DONE EATING OR DEAD */
void		check_if_alive(t_philo *philo);
void		check_if_done_eating(t_philo *philo);
void		is_done_eating_or_dead(t_data *data);
bool		check_stop(t_philo *philo);

/* UTILS */
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
long long	get_current_time(void);
long int	get_time_stamp(t_data *data);
void		ft_display(t_philo *philo, const char *str);

/* THREADS */
void		create_threads(t_data *data);
void		*philo_routine(void *data);
void		wait_threads(t_data *data);

/* DESTROY */
void		destroy_and_free(t_data *data);

/* ACTIONS */
void		philo_eat(t_philo *philo);
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_take_fork(t_philo *philo);
void		drop_forks(t_philo *philo);

#endif