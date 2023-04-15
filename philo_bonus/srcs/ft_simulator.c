/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:14:38 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/04/15 17:10:38 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*ft_run_eat_checker(t_data *data)
{
	int	i;
	int	done_eating;

	if (data->must_eat < 0 && data->size <= 1)
		return (NULL);
	done_eating = 0;
	while (done_eating < data->must_eat)
	{
		i = -1;
		while (++i < data->size + 1)
			sem_wait(data->total_ate_sem);
		done_eating++;
	}
	ft_print_action(data, -1, DONE_EATING, FALSE);
	i = -1;
	if (data->must_eat > 0)
		while (++i < data->size)
			kill(data->philosophers[i]->pid, SIGKILL);
	exit(EXIT_SUCCESS);
	return (NULL);
}

static void	*ft_run_death_checker(t_philo *philo)
{
	long	difference;

	while (1)
	{
		sem_wait(philo->eat_sem);
		difference = (ft_timestamp() - philo->data->start_time) \
				- philo->last_meal;
		if (difference >= philo->data->time_to_die)
		{
			ft_print_action(philo->data, (philo->id + 1), DIED, FALSE);
			exit(EXIT_SUCCESS);
		}
		sem_post(philo->eat_sem);
		ft_usleep(1, philo->data);
	}
	return (NULL);
}

static void	ft_handle_philo_eat(t_philo *philo)
{
	sem_wait(philo->data->forks_sem);
	ft_print_action(philo->data, (philo->id + 1), TOOK_FORK, TRUE);
	sem_wait(philo->data->forks_sem);
	ft_print_action(philo->data, (philo->id + 1), TOOK_FORK, TRUE);
	ft_print_action(philo->data, (philo->id + 1), EATING, TRUE);
	sem_wait(philo->eat_sem);
	memset(&philo->last_meal, philo->data->start_time, sizeof(int));
	ft_usleep(philo->data->time_to_eat, philo->data);
	sem_post(philo->data->total_ate_sem);
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->forks_sem);
	sem_post(philo->eat_sem);
}

static void	ft_handle_philo_life(t_philo *philo)
{
	if (philo->id % 2)
		ft_usleep(100, philo->data);
	while (1)
	{
		ft_handle_philo_eat(philo);
		ft_print_action(philo->data, (philo->id + 1), SLEEPING, TRUE);
		ft_usleep(philo->data->time_to_sleep, philo->data);
		ft_print_action(philo->data, (philo->id + 1), THINKING, TRUE);
	}
}

void	ft_run_simulation(t_data *data)
{
	int	i;

	i = 0;
	if (data->must_eat >= 0 && data->size > 1)
		pthread_create(&data->eat_thread, NULL, \
				(void *) ft_run_eat_checker, data);
	while (i < data->size)
	{
		data->philosophers[i]->pid = fork();
		if (data->philosophers[i]->pid == 0)
		{
			pthread_create(&data->philosophers[i]->death_thread, NULL, \
					(void *) ft_run_death_checker, data->philosophers[i]);
			/* pthread_detach(data->philosophers[i]->death_thread); */
			ft_handle_philo_life(data->philosophers[i]);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}
