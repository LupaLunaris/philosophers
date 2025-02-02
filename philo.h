/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:01:45 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/02 14:41:49 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <signal.h>

# define RST	"\033[0m"
# define RED	"\033[0;31m"
# define GRN	"\033[0;32m"
# define YEL	"\033[0;33m"
# define BLU	"\033[0;34m"
# define MAG	"\033[0;35m"
# define CYN	"\033[0;36m"
# define WHT	"\033[0;37m"
# define ORG    "\033[0;38;5;208m"

typedef pthread_mutex_t	t_mutex;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	int				left_fork_id;
	int				right_fork_id;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
	struct s_data	*data;
	pthread_t		thread;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	bool			someone_died;
	bool			all_ate_enough;
	long long		start_time;
	t_mutex			*forks;
	t_mutex			write_lock;
	t_mutex			death_lock;
	t_mutex			meal_lock;
	t_philo			*philos;
}	t_data;

/* init.c */
int			init_data(t_data *data, char **argv);
void		init_philosophers(t_data *data);
void		init_mutexes(t_data *data);

/* utils.c */
int			ft_atoi(const char *str);
void		clean_exit(t_data *data);
long long	get_time(void);
void		print_status(t_data *data, int id, char *status);
void		accurate_sleep(long long time);

/* actions.c */
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
int			check_death(t_philo *philo);
void		*philosopher_routine(void *arg);

/* monitor.c */
int			start_simulation(t_data *data);
void		*death_monitor(void *arg);
int			check_simulation_end(t_data *data);
int			check_all_ate_enough(t_data *data);
int			check_philosopher_death(t_data *data, int i);

/* main.c */
int			error(char *str);
int			main(int argc, char **argv);

#endif