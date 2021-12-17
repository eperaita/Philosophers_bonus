/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 21:01:26 by eperaita          #+#    #+#             */
/*   Updated: 2021/12/17 19:24:33 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>

typedef struct s_table
{
	struct timeval	startime;
	int				nphilo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				ndinner;
	sem_t			*sem_fork;
	sem_t			*sem_death;
	sem_t			*sem_print;
	int				id;
	int				group;
	struct timeval	eatime;
	int				eated;
	pthread_t		thread;
}	t_table;

//////////PHILO//////
void		philo(t_table *table, int id);

////////TIME//////////
void		*philo_dead(void *table);
long int	o_clock(t_table *table);
int			my_uslip(t_table *table, int time);

///////ROUTINE///////
void		eating(t_table *table);
void		sleeping(t_table *table);
void		thinking(t_table *table);

/////////UTILS////////
int			ft_atoi(const char *str);
#endif
