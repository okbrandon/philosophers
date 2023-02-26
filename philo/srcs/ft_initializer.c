/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initializer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:00:45 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/02/24 21:35:23 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philosopher	*ft_philosophers_init(t_parameters *param)
{
	t_philosopher	*philosophers;
	int				i;

	philosophers = ft_calloc(param->size, sizeof(t_philosopher));
	if (!philosophers)
	{
		ft_error("philosophers allocation went wrong", 0);
		return (NULL);
	}
	i = 0;
	while (i < param->size)
	{
		philosophers[i].id = i + 1;
		philosophers[i].total_ate = 0;
		philosophers[i].is_dead = 0;
		philosophers[i].last_meal = 0;
		pthread_mutex_init(&philosophers[i].fork_mutex, NULL);
		printf("philosopher %d initialized\n", i + 1);
		i++;
	}
	return (philosophers);
}
