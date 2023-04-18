/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulator_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:14:38 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/04/18 16:52:44 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/**
 * @brief Used to run a loop that last until everyone's done eating.
 * It'll bascially wait for a specific semaphore size times.
 * 
 * @param data				- pointer to main data structure
 * @return void*			- ignored
 */
static void	*ft_run_eat_checker(t_data *data)
{
	int	i;

	if (data->must_eat < 0 && data->size <= 1)
		return (NULL);
	i = -1;
	while (++i < data->size)
		sem_wait(data->total_ate_sem);
	if (!data->is_simulating)
		exit(EXIT_SUCCESS);
	ft_print_action(data, -1, DONE_EATING, FALSE);
	i = -1;
	if (data->must_eat > 0)
		while (++i < data->size)
			kill(data->philosophers[i]->pid, SIGTERM);
	exit(EXIT_SUCCESS);
	return (NULL);
}

/**
 * @brief Used to run a loop that last until the tracked philosopher dies.
 * 
 * @param philo				- philosopher to track
 * @return void*			- ignored
 */
static void	*ft_run_death_checker(t_philo *philo)
{
	long	difference;
	long	last_meal;

	while (1)
	{
		sem_wait(philo->eat_sem);
		last_meal = (philo->last_meal.tv_sec * 1000) + \
			(philo->last_meal.tv_usec / 1000);
		difference = ft_timestamp() - last_meal;
		if (difference >= philo->data->time_to_die)
		{
			ft_print_action(philo->data, (philo->id + 1), DIED, FALSE);
			exit(EXIT_FAILURE);
		}
		sem_post(philo->eat_sem);
		ft_usleep(1, philo->data);
	}
	return (NULL);
}

/**
 * @brief First philosopher's eating part. Manages the fork handling
 *  and the eating event.
 * 
 * @param philo				- pointer to a philosopher data
 * @param i					- index of philosopher
 */
static void	ft_handle_philo_eat(t_philo *philo)
{
	sem_wait(philo->data->forks_sem);
	ft_print_action(philo->data, (philo->id + 1), TOOK_FORK, TRUE);
	sem_wait(philo->data->forks_sem);
	ft_print_action(philo->data, (philo->id + 1), TOOK_FORK, TRUE);
	ft_print_action(philo->data, (philo->id + 1), EATING, TRUE);
	sem_wait(philo->eat_sem);
	if (++philo->eat_count == philo->data->must_eat)
		sem_post(philo->data->total_ate_sem);
	gettimeofday(&philo->last_meal, NULL);
	ft_usleep(philo->data->time_to_eat, philo->data);
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->forks_sem);
	sem_post(philo->eat_sem);
}

/**
 * @brief Used to handle the life cycle of a philosopher.
 * 
 * @param philo				- pointer to a philosopher data
 */
static void	ft_handle_philo_life(t_philo *philo)
{
	if (philo->id % 2)
		ft_usleep(1, philo->data);
	while (1)
	{
		ft_handle_philo_eat(philo);
		ft_print_action(philo->data, (philo->id + 1), SLEEPING, TRUE);
		ft_usleep(philo->data->time_to_sleep, philo->data);
		ft_print_action(philo->data, (philo->id + 1), THINKING, TRUE);
	}
}

/**
 * @brief Used to start the philosophers dining problem simulation.
 * It'll exit the simulation if it fails to create each philosopher's fork.
 * 
 * @param data				- pointer to main data stucture
 */
void	ft_run_simulation(t_data *data)
{
	int	i;

	gettimeofday(&data->start_time, NULL);
	if (data->must_eat == 0)
	{
		ft_print_action(data, -1, DONE_EATING, FALSE);
		return ;
	}
	data->is_simulating = TRUE;
	i = -1;
	while (++i < data->size)
	{
		data->philosophers[i]->last_meal = data->start_time;
		data->philosophers[i]->pid = fork();
		if (data->philosophers[i]->pid == 0)
		{
			pthread_create(&data->philosophers[i]->death_thread, NULL, \
					(void *) ft_run_death_checker, data->philosophers[i]);
			ft_handle_philo_life(data->philosophers[i]);
			exit(EXIT_SUCCESS);
		}
	}
	if (data->must_eat >= 0 && data->size > 1)
		pthread_create(&data->eat_thread, NULL, \
				(void *) ft_run_eat_checker, data);
}
