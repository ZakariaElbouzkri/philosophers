/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:51:29 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/05 18:00:06 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

long	check_num(char *s)
{
	long	res;

	res = 0;
	if (!*s)
		return (-1);
	if (*s == '+' && *(s + 1))
		s++;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (-1);
		res *= 10;
		res += (*s - '0');
		if (res > INT_MAX)
			return (-1);
		s++;
	}
	return (res);
}

int	fill_args(char **av, long *args)
{
	int	i;

	i = 0;
	while (av[i])
	{
		args[i] = check_num(av[i]);
		if (args[i] == -1)
			return (0);
		i++;
	}
	return (1);
}

int	init_data(t_data *data, int ac, char **av)
{
	long	*args;

	args = malloc(sizeof(long) * (ac - 1));
	if (!args)
		return (0);
	if (!fill_args(av, args))
		return (free(args), 0);
	data->nbr_of_philo = args[0];
	data->time_to_die = args[1];
	data->time_to_eat = args[2];
	data->time_to_sleep = args[3];
	data->eat_times = (ac == 6) * args[4] + (ac != 6) * (-1);
	data->t0 = current_time();
	data->dead = 0;
	sem_unlink(PR);
	data->pr = sem_open(PR, O_CREAT|O_EXCL, 0777, 1);
	sem_unlink(FORKS);
	data->forks = sem_open(FORKS, O_CREAT|O_EXCL, 0777, data->nbr_of_philo);
	free(args);
	return (1);
}
