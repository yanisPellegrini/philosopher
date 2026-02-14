/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanis <yanis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:10:15 by yanis             #+#    #+#             */
/*   Updated: 2026/02/13 22:10:36 by yanis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* ************************************************************************** */
/*   take_forks - Prend les 2 fourchettes                                   */
/*   ANTI-DEADLOCK: Ordre différent selon l'ID                              */
/*   - Philos PAIRS: prend right puis left                                  */
/*   - Philos IMPAIRS: prend left puis right                                */
/*   Affiche "has taken a fork" pour chaque fourchette                      */
/* ************************************************************************** */

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
	}
}

/* ************************************************************************** */
/*   put_forks - Repose les 2 fourchettes                                   */
/*   Unlock dans le même ordre que lock (pas obligatoire mais plus propre)  */
/* ************************************************************************** */

void	put_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

/* ************************************************************************** */
/*   philosopher_routine - Routine principale du philosophe                 */
/*   Fonction exécutée par chaque thread philo                              */
/*                                                                           */
/*   Cas spécial: 1 seul philosophe                                         */
/*   - Il ne peut prendre qu'1 fourchette                                   */
/*   - Il ne peut pas manger (il faut 2 fourchettes)                        */
/*   - Il attend et meurt                                                   */
/*                                                                           */
/*   Décalage anti-deadlock:                                                */
/*   - Philos pairs attendent 1ms au début                                  */
/*   - Évite que tous prennent leur fourchette gauche en même temps         */
/*                                                                           */
/*   Boucle principale:                                                     */
/*   1. think()                                                             */
/*   2. take_forks()                                                        */
/*   3. eat()                                                               */
/*   4. put_forks()                                                         */
/*   5. philo_sleep()                                                       */
/*   Continue tant qu'aucun philo n'est mort                                */
/* ************************************************************************** */

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num_of_philos == 1)
	{
		print_status(philo, "has taken a fork");
		ft_usleep(philo->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_simulation_stopped(philo))
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		philo_sleep(philo);
	}
	return (NULL);
}