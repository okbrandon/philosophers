/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:13:35 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/03/07 11:16:56 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_error(char *message, int help_needed)
{
	printf("%s%s%sAn error occurred: %s%s\n", \
		RESET, RED, BOLD, RESET, message);
	if (help_needed)
		printf("%s[%s%s?%s] %s\n", RESET, RED, BOLD, RESET, COMMAND);
	return (EXIT_FAILURE);
}

int	ft_timestamp(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

void	ft_print_action(t_data *data, int id, char *action)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%dms %d %s\n", \
		ft_timestamp() - data->start_time, id, action);
	pthread_mutex_unlock(&data->print_mutex);
}

void	ft_usleep(unsigned int time, t_data *data)
{
	unsigned int	start_time;

	start_time = ft_timestamp();
	while (ft_timestamp() - start_time < time)
	{
		if (data->is_there_a_dead)
			return ;
		usleep(1000);
	}
}

/***
 * Don't forget to free all the shit dead ass
*/
void	ft_safe_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->size)
	{
		pthread_mutex_destroy(&data->philosophers->forks[i]);
		printf("philosopher %d destroyed\n", i + 1);
		i++;
	}
	free(data->philosophers->forks);
	free(data->philosophers->last_meal);
	free(data->philosophers->total_ate);
	free(data->philosophers);
	pthread_mutex_destroy(&data->print_mutex);
}
