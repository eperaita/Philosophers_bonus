/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:03:51 by eperaita          #+#    #+#             */
/*   Updated: 2021/12/17 13:42:43 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../philo.h"

static void	print(char *message, t_table *table)
{
	sem_wait(table->sem_print);
	printf("%ld %d %s\n", o_clock(table), table->id, message);
	sem_post(table->sem_print);
}

void	thinking(t_table *table)
{
	if (table->eated)
		print("is thinking", table);
	if (table->nphilo % 2 != 0)
		my_uslip(table, (table->t_eat * 2) - table->t_sleep);
	else if (table->nphilo % 2 == 0)
		my_uslip(table, (table->t_eat - table->t_sleep));
}

void	sleeping(t_table *table)
{
	if (table->eated)
		print("is sleeping", table);
	my_uslip(table, table->t_sleep);
}

void	eating(t_table *table)
{
	sem_wait(table->sem_fork);
	print("has taken a fork", table);
	sem_wait(table->sem_fork);
	print("has taken a fork", table);
	gettimeofday(&table->eatime, NULL);
	print("is eating", table);
	my_uslip(table, table->t_eat);
	sem_post(table->sem_fork);
	sem_post(table->sem_fork);
}
