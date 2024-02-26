/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:09:06 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/26 11:56:51 by bsoubaig         ###   ########.fr       */
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
# include <stdint.h>
# include <stdbool.h>

# define RED 			"\033[0;31m"
# define PURPLE 		"\033[38;5;141m"
# define GREY 			"\033[38;5;240m"
# define GREEN 			"\033[38;5;46m"
# define RESET 			"\033[0m"
# define BOLD 			"\033[1m"

# define COMMAND		"./philo [<philo_num>] [<time_to_die>] [<time_to_eat>] \
[<time_to_sleep>] (<times_each_philo_must_eat>)"
# define TOOK_FORK		"has taken a fork"
# define EATING			"is eating"
# define SLEEPING		"is sleeping"
# define THINKING		"is thinking"
# define DIED			"died"
# define DONE_EATING	"philosophers are done eating"

/**
 * Structure containing philosophers data
 */
typedef struct s_philosophers
{
	int					*total_ate;
	int					*done_eating;
	long				*last_meal;
	pthread_mutex_t		*forks;
	pthread_t			*threads;
	int					**hands;
}				t_philosophers;

/**
 * Main structure containing all data
 */
typedef struct s_data
{
	int						size;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat;
	int						eat_count;
	int						done_eating;
	int						current_philo_id;
	int						threads_done;
	long					start_time;
	bool					is_simulating;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			var_modification;
	pthread_mutex_t			var_read;
	pthread_mutex_t			sim_read;
	pthread_mutex_t			philo_life_init;
	struct s_philosophers	*philosophers;
}				t_data;

/**
 * ft_args_handler.c
 */
bool			ft_check_args(int argc, char **argv);
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
int				ft_error(char *message, bool help_needed);
void			ft_print_action(t_data *data, int id, char *action, \
								bool is_death);
void			ft_usleep(unsigned int time, t_data *data);
void			ft_safe_exit(t_data *data);

/*
 * ft_simulator_utils.c
 */
bool			ft_check_philosophers_meals(t_data *data);
long			ft_timestamp(void);
bool			ft_is_simulating(t_data *data);
void			ft_update_simulation(t_data *data, bool status);

/*
 * ft_simulator.c
 */
void			ft_run_watcher(t_data *data);
void			ft_run_single_simulation(t_data *data);
void			ft_run_simulation(t_data *data);
void			ft_wait_for_threads(t_data *data);

#endif