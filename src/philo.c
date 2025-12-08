/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypellegr <ypellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:52:16 by ypellegr          #+#    #+#             */
/*   Updated: 2025/12/08 12:10:39 by ypellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int check_args(int ac, char **av, )
{
	int i;
	int j;

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
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
	{
		write(2, "Error: Number of philosophers must be greater than 0.\n", 55);
		return (1);
	} else if (ft_atoi(av[1]) > 200)
	{
		write(2, "Error: Number of philosophers must be less than or equal to 200.\n", 66);
		return (1);
	}
	return (0);
}

int main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return (1);
	}
	
}
