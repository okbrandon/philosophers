/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:13:35 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/02/27 15:34:36 by bsoubaig         ###   ########.fr       */
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

void	ft_print_action(t_parameters param, int id, char *action)
{
	pthread_mutex_lock(&param.print_mutex);
	printf("%dms %d %s\n", \
		ft_timestamp() - param.start_time, id, action);
	pthread_mutex_unlock(&param.print_mutex);
}

void	ft_usleep(unsigned int time, t_parameters param)
{
	unsigned int	start_time;

	start_time = ft_timestamp();
	while (ft_timestamp() - start_time < time)
	{
		if (param.dead)
			return ;
		usleep(1000);
	}
}

void	ft_safe_exit(t_parameters param)
{
	int	i;

	i = 0;
	while (i < param.size)
	{
		pthread_mutex_destroy(&param.philosophers[i].fork_mutex);
		printf("philosopher %d destroyed\n", i + 1);
		i++;
	}
	pthread_mutex_destroy(&param.print_mutex);
	free(param.philosophers);
}
