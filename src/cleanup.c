/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanis <yanis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:13:04 by yanis             #+#    #+#             */
/*   Updated: 2026/02/13 22:14:22 by yanis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* ************************************************************************** */
/*   destroy_mutexes - Détruit tous les mutex                               */
/*   1. Détruit les N mutex des fourchettes                                 */
/*   2. Détruit les 3 mutex globaux (dead_lock, meal_lock, write_lock)      */
/* ************************************************************************** */

void	destroy_mutexes(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		pthread_mutex_destroy(&program->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
}

/* ************************************************************************** */
/*   cleanup - Libère toute la mémoire et détruit les mutex                 */
/*   Ordre:                                                                  */
/*   1. Détruit tous les mutex                                              */
/*   2. Free le tableau de fourchettes                                      */
/*   3. Free le tableau de philosophes                                      */
/* ************************************************************************** */

void	cleanup(t_program *program)
{
	destroy_mutexes(program);
	free(program->forks);
	free(program->philos);
}