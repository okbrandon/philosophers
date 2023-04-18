/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initializer_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:24:15 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/04/18 12:25:45 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/**
 * @brief Used to initialized each semaphore from the data structure.
 * 
 * @param data				- pointer to main data structure
 * @return int				- returns if there's a problem or not
 */
static int	ft_init_semaphores(t_data *data)
{
	sem_unlink(EAT_SEM_NAME);
	sem_unlink(WRITE_SEM_NAME);
	sem_unlink(FORKS_SEM_NAME);
	data->total_ate_sem = sem_open(EAT_SEM_NAME, O_CREAT | O_EXCL, 0664, 0);
	if (data->total_ate_sem == SEM_FAILED)
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

/**
 * @brief Used to return an initialized philosophers structure.
 * This structure contains all needed data from each philosopher.
 * 
 * @param data				- main data structure
 * @return t_philo**		- pointer to philosophers structure
 */
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

/**
 * @brief Used to return an initialized data structure.
 * This structure contains all needed data from the program
 *  and also a pointer to each philosopher's data.
 * 
 * @param argv				- argv from main program
 * @return t_data*			- pointer to data structure
 */
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
	return (data);
}
