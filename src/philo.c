/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanis <yanis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:52:16 by ypellegr          #+#    #+#             */
/*   Updated: 2026/02/13 21:37:16 by yanis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* ************************************************************************** */
/*   is_number - Vérifie qu'une string ne contient que des chiffres         */
/*   Retourne 1 si c'est un nombre valide, 0 sinon                          */
/* ************************************************************************** */

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*   check_args - Validation complète des arguments                         */
/*   1. Vérifie que tous les arguments sont des nombres                     */
/*   2. Vérifie que number_of_philosophers > 0 et <= 200                    */
/*   3. Vérifie que time_to_die, time_to_eat, time_to_sleep > 0            */
/* ************************************************************************** */

int	check_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
	{
		printf("Error: Invalid number of arguments\n");
		printf("Usage: ./philo nb_philos time_die time_eat time_sleep ");
		printf("[nb_must_eat]\n");
		return (1);
	}
	i = 1;
	while (i < ac)
	{
		if (!is_number(av[i]))
		{
			printf("Error: Invalid argument '%s' (must be a positive number)\n",
				av[i]);
			return (1);
		}
		i++;
	}
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > 200)
	{
		printf("Error: Number of philosophers must be between 1 and 200\n");
		return (1);
	}
	if (ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
	{
		printf("Error: Time values must be greater than 0\n");
		return (1);
	}
	if (ac == 6 && ft_atoi(av[5]) <= 0)
	{
		printf("Error: Number of meals must be greater than 0\n");
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*   start_simulation - Lance tous les threads                              */
/*   1. Crée un thread pour chaque philosophe                               */
/*   2. Crée le thread de monitoring                                        */
/*   3. Attend que tous les threads se terminent (join)                     */
/* ************************************************************************** */

int	start_simulation(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
				philosopher_routine, &program->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&program->monitor, NULL, monitor_routine, program) != 0)
		return (1);
	i = 0;
	while (i < program->num_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
	pthread_join(program->monitor, NULL);
	return (0);
}

/* ************************************************************************** */
/*   main - Point d'entrée du programme                                     */
/*   1. Valide les arguments                                                */
/*   2. Initialise le programme                                             */
/*   3. Lance la simulation                                                 */
/*   4. Nettoie la mémoire                                                  */
/* ************************************************************************** */

int	main(int ac, char **av)
{
	t_program	program;

	if (check_args(ac, av) != 0)
		return (1);
	if (init_program(&program, ac, av) != 0)
	{
		printf("Error: Initialization failed\n");
		return (1);
	}
	if (start_simulation(&program) != 0)
	{
		printf("Error: Simulation failed\n");
		cleanup(&program);
		return (1);
	}
	cleanup(&program);
	return (0);
}

