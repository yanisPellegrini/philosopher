/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypellegr <ypellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:52:16 by ypellegr          #+#    #+#             */
/*   Updated: 2025/12/11 09:42:21 by ypellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	args_eror(char **av)
{
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0
		|| ft_atoi(av[4]) <= 0)
	{
		write(2, "Error: Number of philosophers must be greater than 0.\n", 55);
		return (1);
	}
	else if (ft_atoi(av[1]) > 200)
	{
		write(2,
			"Error: Number of philosophers must be less than or equal to 200.\n",
			66);
		return (1);
	}
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				write(2, "Error: Invalid argument '", 25);
				return (1);
			}
			j++;
		}
		i++;
	}
	if (args_eror(av) == 1)
		return (1);
	return (0);
}

int init_philo(t_program *program, int ac, char **av)
{
	int i;

	i = 0;
	while (i != ft_atoi(av[1]))
	{
		program->philos[i].id = i + 1;
		program->philos[i].time_to_die = ft_atoi(av[2]);
		program->philos[i].time_to_eat = ft_atoi(av[3]);
		program->philos[i].time_to_sleep = ft_atoi(av[4]);
		program->philos[i].num_of_philos = ft_atoi(av[1]);
		program->philos[i].meals_eaten = 0;
		program->philos[i].eating = 0;
		program->philos[i].start_time = get_time();
		program->philos[i].last_meal = program->philos[i].start_time;
		program->philos[i].dead = &program->dead_flag;
		program->philos[i].write_lock = &program->write_lock;
		program->philos[i].dead_lock = &program->dead_lock;
		program->philos[i].meal_lock = &program->meal_lock;
		if (ac == 6)
			program->philos[i].num_times_to_eat = ft_atoi(av[5]);
		i++;
	}
	return (0);
}

int init_mutexs(t_program *program, int ac, char **av)
{
	int i;

	i = 0;
	while (i != ft_atoi(av[1]))
	{
		if (pthread_mutex_init(&program->philos[i].l_fork, NULL) != 0)
			return (1);
		if (i == ft_atoi(av[1]) - 1)
			program->philos[i].r_fork = &program->philos[0].l_fork;
		else
			program->philos[i].r_fork = &program->philos[i + 1].l_fork;
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

int init_program(t_program *program, int ac, char **av)
{
	if (init_philo(program, ac, av) == 1)
		return (1);
	if (init_mutexes(program, ac, av) == 1)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_program	program;
	if (ac < 5 || ac > 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return (1);
	}
	if (check_args(ac, av) == 1)
		return (1);
	if (init_program(&program, ac, av) == 1)
		return (1);
	if (start_simulation(&program) == 1)
		return (1);
	return (0);
}
