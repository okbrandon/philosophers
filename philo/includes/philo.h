/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:09:06 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/03/12 11:55:23 by bsoubaig         ###   ########.fr       */
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

# define COMMAND	"./philo [<philo_num>] [<time_to_die>] [<time_to_eat>] \
[<time_to_sleep>] (<times_each_philo_must_eat>)"
# define TOOK_FORK	"has taken a fork"
# define EATING		"is eating"
# define SLEEPING	"is sleeping"
# define THINKING	"is thinking"
# define DIED		"died"

# define TRUE		1
# define FALSE		0

typedef struct s_philosophers
{
	int					*total_ate;
	long				*last_meal;
	pthread_mutex_t		*forks;
	pthread_t			*threads;
}				t_philosophers;

typedef struct s_data
{
	int						start_time;
	int						size;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat;
	int						is_simulating;
	int						current_philo_id;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			var_modification;
	pthread_mutex_t			philo_life_init;
	struct s_philosophers	*philosophers;
}				t_data;

/**
 * ft_args_handler.c
 */
int				ft_check_args(int argc, char **argv);
void			ft_parse_args(t_data *data, char **argv);

/**
 * ft_initializer.c
*/
t_data			*ft_data_init(char **argv);
t_philosophers	*ft_philosophers_init(t_data *data);

/**
 * ft_libft_utils.c
*/
int				ft_atoi(char *str);
void			*ft_calloc(size_t count, size_t size);

/*
 * ft_other_utils.c
 */
int				ft_error(char *message, int help_needed);
int				ft_timestamp(void);
void			ft_print_action(t_data *data, int id, char *action, \
								int do_unlock);
void			ft_usleep(unsigned int time, t_data *data);
void			ft_safe_exit(t_data *data);

/*
 * ft_simulator.c
 */
void			ft_run_death_checker(t_data *data);
void			ft_run_simulation(t_data *data);

#endif