/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanis <yanis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:12:11 by yanis             #+#    #+#             */
/*   Updated: 2026/02/13 22:41:05 by yanis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../philo.h"

/* ************************************************************************** */
/*   is_simulation_stopped - Vérifie si la simulation doit s'arrêter        */
/*   Thread-safe: vérifie dead_flag avec mutex                              */
/*   Retourne 1 si arrêté, 0 sinon                                          */
/* ************************************************************************** */

int	is_simulation_stopped(t_philo *philo)
{
	int	stopped;

	pthread_mutex_lock(philo->dead_lock);
	stopped = *philo->dead_flag;
	pthread_mutex_unlock(philo->dead_lock);
	return (stopped);
}

/* ************************************************************************** */
/*   check_death - Vérifie si un philosophe est mort                        */
/*   Calcul: (current_time - last_meal) >= time_to_die                      */
/*   Thread-safe: last_meal protégé par meal_lock                           */
/*   Retourne 1 si mort, 0 sinon                                            */
/* ************************************************************************** */

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

/* ************************************************************************** */
/*   check_all_ate - Vérifie si tous les philos ont assez mangé             */
/*   Si num_times_to_eat n'est pas spécifié (-1), retourne 0                */
/*   Sinon, vérifie que tous ont mangé >= num_times_to_eat                  */
/*   Thread-safe: meals_eaten protégé par meal_lock                         */
/*   Retourne 1 si tous ont assez mangé, 0 sinon                            */
/* ************************************************************************** */

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
		if (program->philos[i].meals_eaten < program->philos[i].num_times_to_eat)
			all_ate = 0;
		pthread_mutex_unlock(&program->meal_lock);
		i++;
	}
	return (all_ate);
}

/* ************************************************************************** */
/*   monitor_routine - Thread de surveillance                               */
/*   Vérifie en boucle:                                                     */
/*   1. Si un philosophe est mort                                           */
/*   2. Si tous ont assez mangé                                             */
/*                                                                           */
/*   Quand un philo meurt:                                                  */
/*   - Affiche "X died" (avec write_lock pour éviter chevauchement)         */
/*   - Set dead_flag = 1                                                    */
/*   - Retourne → arrête la simulation                                      */
/*                                                                           */
/*   Quand tous ont mangé:                                                  */
/*   - Set all_ate_flag = 1                                                 */
/*   - Set dead_flag = 1 (pour arrêter les threads philos)                  */
/*   - Retourne → arrête la simulation                                      */
/*                                                                           */
/*   Note: usleep(500) = check toutes les 0.5ms                             */
/*   Assez rapide pour détecter la mort dans les 10ms requis                */
/* ************************************************************************** */

void	*monitor_routine(void *arg)
{
	t_program	*program;
	int			i;

	program = (t_program *)arg;
	while (1)
	{
		i = 0;
		while (i < program->num_philos)
		{
			if (check_death(&program->philos[i]))
			{
				pthread_mutex_lock(&program->write_lock);
				pthread_mutex_lock(&program->dead_lock);
				program->dead_flag = 1;
				printf("%zu %d died\n", get_time() - program->philos[i].start_time,
					program->philos[i].id);
				pthread_mutex_unlock(&program->dead_lock);
				pthread_mutex_unlock(&program->write_lock);
				return (NULL);
			}
			i++;
		}
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
