/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanis <yanis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:08:18 by yanis             #+#    #+#             */
/*   Updated: 2026/02/14 07:47:18 by yanis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../philo.h"

/* ************************************************************************** */
/*   eat - Le philosophe mange                                              */
/*   1. Affiche "is eating"                                                 */
/*   2. Update last_meal (protégé par meal_lock)                            */
/*   3. Sleep pendant time_to_eat                                           */
/*   4. Incrémente meals_eaten (protégé par meal_lock)                      */
/* ************************************************************************** */

void	eat(t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
}

/* ************************************************************************** */
/*   philo_sleep - Le philosophe dort                                       */
/*   1. Affiche "is sleeping"                                               */
/*   2. Sleep pendant time_to_sleep                                         */
/* ************************************************************************** */

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

/* ************************************************************************** */
/*   think - Le philosophe pense                                            */
/*   Affiche simplement "is thinking"                                       */
/* ************************************************************************** */

void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
	usleep(1000);
}