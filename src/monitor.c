/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypellegr <ypellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:12:11 by yanis             #+#    #+#             */
/*   Updated: 2026/02/14 14:22:17 by ypellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_simulation_stopped(t_philo *philo)
{
	int	stopped;

	pthread_mutex_lock(philo->dead_lock);
	stopped = *philo->dead_flag;
	pthread_mutex_unlock(philo->dead_lock);
	return (stopped);
}

int	check_death(t_philo *philo)
{
	size_t	time_since_meal;

	pthread_mutex_lock(philo->meal_lock);
	time_since_meal = get_time() - philo->last_meal;
	pthread_mutex_unlock(philo->meal_lock);
	if (time_since_meal >= philo->time_to_die)
		return (1);
	return (0);
}

int	check_all_ate(t_program *program)
{
	int	i;
	int	all_ate;

	if (program->philos[0].num_times_to_eat == -1)
		return (0);
	all_ate = 1;
	i = 0;
	while (i < program->num_philos)
	{
		pthread_mutex_lock(&program->meal_lock);
		if (program->philos[i].meals_eaten < program->philos
			[i].num_times_to_eat)
			all_ate = 0;
		pthread_mutex_unlock(&program->meal_lock);
		i++;
	}
	return (all_ate);
}

void	print_death(t_program *program, int i)
{
	pthread_mutex_lock(&program->write_lock);
	pthread_mutex_lock(&program->dead_lock);
	program->dead_flag = 1;
	printf("%zu %d died\n", get_time() - program->philos[i].start_time,
		program->philos[i].id);
	pthread_mutex_unlock(&program->dead_lock);
	pthread_mutex_unlock(&program->write_lock);
}

void	*monitor_routine(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	while (1)
	{
		if (check_philo(program))
			return (NULL);
		if (check_all_ate(program))
		{
			pthread_mutex_lock(&program->dead_lock);
			program->dead_flag = 1;
			program->all_ate_flag = 1;
			pthread_mutex_unlock(&program->dead_lock);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
