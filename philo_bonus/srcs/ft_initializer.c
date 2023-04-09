/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initializer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:24:15 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/04/08 23:11:41 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_init_semaphores(t_data *data)
{
	sem_unlink(EAT_SEM_NAME);
	sem_unlink(WRITE_SEM_NAME);
	sem_unlink(FORKS_SEM_NAME);
	data->eat_sem = sem_open(EAT_SEM_NAME, O_CREAT | O_EXCL, 0664, 1);
	if (data->eat_sem == SEM_FAILED)
		return (1);
	data->print_sem = sem_open(WRITE_SEM_NAME, O_CREAT | O_EXCL, 0664, 1);
	if (data->print_sem == SEM_FAILED)
		return (1);
	data->forks_sem = sem_open(FORKS_SEM_NAME, O_CREAT | O_EXCL, 0664, \
			data->size);
	if (data->forks_sem == SEM_FAILED)
		return (1);
	return (0);
}

static t_philo	**ft_init_philosophers(t_data *data)
{
	t_philo	**philos;
	int		i;

	philos = ft_calloc(data->size, sizeof(t_philo *));
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < data->size)
	{
		philos[i] = ft_calloc(1, sizeof(t_philo));
		if (!philos[i])
			return (NULL);
		philos[i]->data = data;
		philos[i]->id = i;
		sem_unlink(PEAT_SEM_NAME);
		philos[i]->eat_sem = sem_open(PEAT_SEM_NAME, O_CREAT | O_EXCL, 0664, 1);
		if (philos[i]->eat_sem == SEM_FAILED)
			return (NULL);
	}
	return (philos);
}

t_data	*ft_data_init(char **argv)
{
	t_data	*data;
	t_philo	**philosophers;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
	{
		ft_error("data allocation went wrong", 0);
		return (NULL);
	}
	ft_parse_args(data, argv);
	if (ft_init_semaphores(data))
	{
		ft_error("semaphore allocation went wrong", 0);
		return (NULL);
	}
	philosophers = ft_init_philosophers(data);
	if (!philosophers)
	{
		ft_error("philosophers allocation went wrong", 0);
		return (NULL);
	}
	data->philosophers = philosophers;
	data->start_time = ft_timestamp();
	return (data);
}
