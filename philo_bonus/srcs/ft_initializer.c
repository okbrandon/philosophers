/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initializer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:24:15 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/04/01 18:16:09 by bsoubaig         ###   ########.fr       */
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
	t_philo	**philosophers;
	int		i;

	philosophers = ft_calloc(data->size, sizeof(t_philo *));
	if (!philosophers)
		return (NULL);
	i = -1;
	while (++i < data->size)
	{
		philosophers[i] = ft_calloc(1, sizeof(t_philo));
		if (!philosophers[i])
			return (NULL);
		philosophers[i]->data = data;
		philosophers[i]->id = i;
		sem_unlink("/eat_count");
		philosophers[i]->eat_sem = sem_open("/eat_count", O_CREAT | O_EXCL, 0664, 1);
		if (philosophers[i]->eat_sem == SEM_FAILED)
			return (NULL);
	}
	return (philosophers);
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
