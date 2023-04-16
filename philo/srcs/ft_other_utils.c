/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:13:35 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/04/16 12:15:21 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_error(char *message, int help_needed)
{
	printf("%s%s%sAn error occurred: %s%s\n", \
		RESET, RED, BOLD, RESET, message);
	if (help_needed)
		printf("---\n%s%s[%s%s?%s%s]%s Need help?\n%s»%s%s»%s%s»%s %s\n", \
			RESET, BOLD, RED, BOLD, RESET, BOLD, \
			RESET, BOLD, RED, BOLD, RESET, BOLD, RESET, COMMAND);
	return (EXIT_FAILURE);
}

long	ft_timestamp(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

void	ft_print_action(t_data *data, int id, char *action, int do_unlock)
{
	pthread_mutex_lock(&data->print_mutex);
	if (DO_PRINT)
	{
		if (id >= 0)
			printf("%-6ld %6d %s\n", \
				ft_timestamp() - data->start_time, id, action);
		else
			printf("%-11ld %s\n", \
				ft_timestamp() - data->start_time, action);
	}
	if (do_unlock)
		pthread_mutex_unlock(&data->print_mutex);
}

void	ft_usleep(unsigned int time, t_data *data)
{
	unsigned int	end_time;

	if (time > 0)
	{
		end_time = ft_timestamp() + time;
		while ((unsigned int) ft_timestamp() < end_time)
			usleep(data->size * 2);
	}
}

/***
 * Don't forget to free all the shit dead ass
*/
void	ft_safe_exit(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->var_modification);
	pthread_mutex_destroy(&data->var_read);
	pthread_mutex_destroy(&data->philo_life_init);
	i = 0;
	while (i < data->size)
	{
		pthread_mutex_destroy(&data->philosophers->forks[i]);
		pthread_detach(data->philosophers->threads[i]);
		i++;
	}
	free(data->philosophers->forks);
	free(data->philosophers->done_eating);
	free(data->philosophers->last_meal);
	free(data->philosophers->total_ate);
	free(data->philosophers->threads);
	free(data->philosophers);
}
