/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypellegr <ypellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:52:34 by ypellegr          #+#    #+#             */
/*   Updated: 2026/02/14 13:46:15 by ypellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	int				*dead_flag;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				num_philos;
	int				dead_flag;
	int				all_ate_flag;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

int					ft_atoi(const char *str);
size_t				get_time(void);
void				ft_usleep(size_t milliseconds);
void				print_status(t_philo *philo, char *status);
int					init_program(t_program *program, int ac, char **av);
int					init_philos(t_program *program, char **av);
int					init_mutexes(t_program *program);
void				init_forks(t_program *program);
void				*philosopher_routine(void *arg);
void				take_forks(t_philo *philo);
void				put_forks(t_philo *philo);
void				eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				think(t_philo *philo);
void				*monitor_routine(void *arg);
int					check_death(t_philo *philo);
int					check_all_ate(t_program *program);
int					is_simulation_stopped(t_philo *philo);
void				destroy_mutexes(t_program *program);
void				cleanup(t_program *program);
int					check_args(int ac, char **av);
int					check_arg_count(int ac);
int					check_arg_format(int ac, char **av);
int					check_arg_values(int ac, char **av);
int					start_simulation(t_program *program);
void				print_death(t_program *program, int i);
int					check_philo(t_program *program);
int					allocate_memory(t_program *program);

#endif
