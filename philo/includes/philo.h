/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:09:06 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/02/21 16:56:08 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define RED 		"\033[0;31m"
# define PURPLE 	"\033[38;5;141m"
# define GREY 		"\033[38;5;240m"
# define GREEN 		"\033[38;5;46m"
# define RESET 		"\033[0m"
# define BOLD 		"\033[1m"

# define COMMAND	"./philo <number_of_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> <(number_of_times_each_philosopher_must_eat)>"

typedef struct s_parameters
{
	int		philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;
}			t_parameters;

typedef struct s_philosopher
{
	int					id;
	int					total_ate;
	long				last_meal;
	struct s_parameters	*parameters;
}				t_philosopher;

/**
 * ft_args_checker.c
 */
int		ft_check_args(int argc, char **argv);

/**
 * ft_args_parser.c
 */
int		ft_parse_args(t_parameters *param, char **argv);

/*
 * ft_other_utils.c
 */
int		ft_error(char *message, int help_needed);
int		ft_atoi(char *str);
void	*ft_calloc(size_t count, size_t size);

#endif