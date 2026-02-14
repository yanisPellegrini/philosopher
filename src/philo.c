/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypellegr <ypellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:52:16 by ypellegr          #+#    #+#             */
/*   Updated: 2026/02/14 12:43:19 by ypellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_number(char *str)
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

int	check_arg_count(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: Invalid number of arguments\n");
		printf("Usage: ./philo nb_philos time_die time_eat time_sleep ");
		printf("[nb_must_eat]\n");
		return (1);
	}
	return (0);
}

int	check_arg_format(int ac, char **av)
{
	int	i;

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
	return (0);
}

int	check_arg_values(int ac, char **av)
{
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
