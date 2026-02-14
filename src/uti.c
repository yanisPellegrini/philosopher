/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanis <yanis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 20:58:43 by yanis             #+#    #+#             */
/*   Updated: 2026/02/13 21:29:56 by yanis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

size_t get_time(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec *1000) + (time.tv_usec / 1000));
}

void ft_usleep(size_t milliseconds)
{
    size_t start;

    start = get_time();
    while((get_time() - start) < milliseconds)
        usleep(500);
}

void print_status(t_philo *philo, char *status)
{
    size_t timestamp;

    pthread_mutex_lock(philo->write_lock);
    pthread_mutex_lock(philo->dead_lock);
    if(*philo->dead_flag == 0)
    {
        timestamp = get_time() - philo->start_time;
        printf("%zu %d %s\n", timestamp, philo->id, status);
    }
    pthread_mutex_unlock(philo->dead_lock);
    pthread_mutex_unlock(philo->write_lock);
}

