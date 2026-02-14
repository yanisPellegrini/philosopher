/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanis <yanis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:33:44 by yanis             #+#    #+#             */
/*   Updated: 2026/02/13 22:41:04 by yanis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* ************************************************************************** */
/*   init_forks - Assigne les fourchettes left et right à chaque philo      */
/*   Philo 0 a fork[0] à gauche et fork[1] à droite                         */
/*   Dernier philo a fork[N-1] à gauche et fork[0] à droite (table ronde)   */
/* ************************************************************************** */

void	init_forks(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		program->philos[i].l_fork = &program->forks[i];
		program->philos[i].r_fork = &program->forks[(i + 1)
			% program->num_philos];
		i++;
	}
}

/* ************************************************************************** */
/*   init_philos - Remplit le tableau de philosophes avec les données       */
/*   Chaque philo reçoit: id, timing, pointeurs partagés                    */
/* ************************************************************************** */

int	init_philos(t_program *program, char **av)
{
	int		i;
	size_t	start_time;

	start_time = get_time();
	i = 0;
	while (i < program->num_philos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].eating = 0;
		program->philos[i].meals_eaten = 0;
		program->philos[i].last_meal = start_time;
		program->philos[i].time_to_die = ft_atoi(av[2]);
		program->philos[i].time_to_eat = ft_atoi(av[3]);
		program->philos[i].time_to_sleep = ft_atoi(av[4]);
		program->philos[i].start_time = start_time;
		program->philos[i].num_of_philos = program->num_philos;
		program->philos[i].num_times_to_eat = -1;
		if (av[5])
			program->philos[i].num_times_to_eat = ft_atoi(av[5]);
		program->philos[i].dead_flag = &program->dead_flag;
		program->philos[i].write_lock = &program->write_lock;
		program->philos[i].dead_lock = &program->dead_lock;
		program->philos[i].meal_lock = &program->meal_lock;
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*   init_mutexes - Initialise tous les mutex du programme                  */
/*   - N mutex pour les fourchettes                                         */
/*   - 3 mutex globaux (dead_lock, meal_lock, write_lock)                   */
/* ************************************************************************** */

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

/* ************************************************************************** */
/*   init_program - Initialise tout le programme                            */
/*   1. Parse le nombre de philos                                           */
/*   2. Alloue la mémoire (philos + forks)                                  */
/*   3. Initialise les mutex                                                */
/*   4. Initialise les philosophes                                          */
/*   5. Assigne les fourchettes                                             */
/* ************************************************************************** */

int	init_program(t_program *program, int ac, char **av)
{
	program->num_philos = ft_atoi(av[1]);
	program->dead_flag = 0;
	program->all_ate_flag = 0;
	program->philos = malloc(sizeof(t_philo) * program->num_philos);
	if (!program->philos)
		return (1);
	program->forks = malloc(sizeof(pthread_mutex_t) * program->num_philos);
	if (!program->forks)
	{
		free(program->philos);
		return (1);
	}
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
