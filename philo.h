/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:01:45 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/11 15:11:57 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define RST    "\033[0m"
# define RED    "\033[0;31m"
# define GRN    "\033[0;32m"
# define YEL    "\033[0;33m"
# define BLU    "\033[0;34m"
# define MAG    "\033[0;35m"
# define CYN    "\033[0;36m"
# define WHT    "\033[0;37m"
# define ORG    "\033[0;38;5;208m"

typedef struct s_philo	t_philo;
typedef struct s_state	t_state;

struct s_philo
{
	int				id;
	long			last_meal;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	pthread_t		thread;
	t_state			*state;
};

struct s_state
{
	int				philo_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_to_eat;
	int				stop_simulation;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	stop_lock;
	t_philo			*philosophers;
	pthread_mutex_t	end_lock;
	int				threads_done;
	pthread_mutex_t	priority_lock;
};

// init.c
int		init_state(t_state *state, int argc, char **argv);
int		init_philosophers(t_state *state);

// routine.c
void	*philosopher_routine(void *arg);
int		take_forks(t_philo *philo);
int		eating_routine(t_philo *philo);

// monitor.c
void	monitor_simulation(t_state *state);

// utils.c
long	get_current_time(void);
void	smart_sleep(long duration);
void	print_status(t_philo *philo, char *status);
int		simulation_should_stop(t_state *state);
int		ft_atoi(const char *str);

#endif
