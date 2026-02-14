/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypellegr <ypellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:33:44 by yanis             #+#    #+#             */
/*   Updated: 2026/02/14 14:21:36 by ypellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philo_data(t_philo *philo, int i, char **av, size_t start_time)
{
	philo->id = i + 1;
	philo->eating = 0;
	philo->meals_eaten = 0;
	philo->last_meal = start_time;
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->start_time = start_time;
	philo->num_times_to_eat = -1;
	if (av[5])
		philo->num_times_to_eat = ft_atoi(av[5]);
}

void	init_philo_pointers(t_philo *philo, t_program *program)
{
	philo->num_of_philos = program->num_philos;
	philo->dead_flag = &program->dead_flag;
	philo->write_lock = &program->write_lock;
	philo->dead_lock = &program->dead_lock;
	philo->meal_lock = &program->meal_lock;
}

int	init_philos(t_program *program, char **av)
{
	int		i;
	size_t	start_time;

	start_time = get_time();
	i = 0;
	while (i < program->num_philos)
	{
		init_philo_data(&program->philos[i], i, av, start_time);
		init_philo_pointers(&program->philos[i], program);
		i++;
	}
	return (0);
}

int	init_mutexes(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&program->dead_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&program->meal_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&program->write_lock, NULL) != 0)
		return (1);
	return (0);
}

int	init_program(t_program *program, int ac, char **av)
{
	program->num_philos = ft_atoi(av[1]);
	program->dead_flag = 0;
	program->all_ate_flag = 0;
	if (allocate_memory(program) != 0)
		return (1);
	if (init_mutexes(program) != 0)
	{
		free(program->philos);
		free(program->forks);
		return (1);
	}
	if (init_philos(program, av) != 0)
		return (1);
	init_forks(program);
	(void)ac;
	return (0);
}
