/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uti2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypellegr <ypellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:33:14 by ypellegr          #+#    #+#             */
/*   Updated: 2026/02/14 14:21:53 by ypellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_philo(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		if (check_death(&program->philos[i]))
		{
			print_death(program, i);
			return (1);
		}
		i++;
	}
	return (0);
}

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

int	check_args(int ac, char **av)
{
	if (check_arg_count(ac) != 0)
		return (1);
	if (check_arg_format(ac, av) != 0)
		return (1);
	if (check_arg_values(ac, av) != 0)
		return (1);
	return (0);
}

int	start_simulation(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->num_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
				philosopher_routine, &program->philos[i]))
			return (1);
	}
	if (pthread_create(&program->monitor, NULL, monitor_routine, program))
		return (1);
	i = -1;
	while (++i < program->num_philos)
		pthread_join(program->philos[i].thread, NULL);
	pthread_join(program->monitor, NULL);
	return (0);
}

int	allocate_memory(t_program *program)
{
	program->philos = malloc(sizeof(t_philo) * program->num_philos);
	if (!program->philos)
		return (1);
	program->forks = malloc(sizeof(pthread_mutex_t) * program->num_philos);
	if (!program->forks)
	{
		free(program->philos);
		return (1);
	}
	return (0);
}
