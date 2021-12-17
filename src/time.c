/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:28:38 by eperaita          #+#    #+#             */
/*   Updated: 2021/12/17 19:19:39 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include "../philo.h"

/////////////////////////DEADS///////////////////

int	is_dead(t_table *table)
{
	struct timeval	now;
	long int		period;

	gettimeofday(&now, NULL);
	period = (now.tv_sec * 1000 + now.tv_usec / 1000)
		- (table->eatime.tv_sec * 1000 + table->eatime.tv_usec / 1000);
	if (period > table->t_die)
		return (1);
	return (0);
}

void	*philo_dead(void *table)
{
	while (1)
	{
		sem_wait(((t_table *)table)->sem_death);
		if (is_dead((t_table *)table))
		{
			printf("%ld %d died\n", o_clock((t_table *)table),
				((t_table *)table)->id);
			exit(1);
		}
		sem_post(((t_table *)table)->sem_death);
		usleep(900);
	}
	return (NULL);
}

////////////////// TIMESTAMP //////////////////

long int	o_clock(t_table *table)
{
	struct timeval	now;
	long int		ms;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec * 1000 + now.tv_usec / 1000)
		- (table->startime.tv_sec * 1000
			+ table->startime.tv_usec / 1000);
	return (ms);
}

//////////////////MY USLIP //////////////////////////

int	my_uslip(t_table *table, int time)
{
	struct timeval	now;
	struct timeval	end;
	int				i;

	(void)table;
	gettimeofday(&now, NULL);
	gettimeofday(&end, NULL);
	i = 0;
	while ((end.tv_sec * 1000 + end.tv_usec / 1000)
		- (now.tv_sec * 1000 + now.tv_usec / 1000) < time)
	{
		usleep(100);
		gettimeofday(&end, NULL);
	}
	return (0);
}
