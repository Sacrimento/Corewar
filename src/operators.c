/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:36:15 by mfonteni          #+#    #+#             */
/*   Updated: 2018/05/22 13:54:57 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int and (t_process *process, int *reg1, int *reg2, int *reg3)
{
	if (!reg1 || !reg2 || !reg3)
		return (process->carry = 0);
	*reg3 = *reg1 & *reg2;
	return (process->carry = 1);
}

int or (t_process *process, int *reg1, int *reg2, int *reg3)
{
	if (!reg1 || !reg2 || !reg3)
		return (process->carry = 0);
	*reg3 = *reg1 | *reg2;
	return (process->carry = 1);
}

int xor (t_process *process, int *reg1, int *reg2, int *reg3)
{
	if (!reg1 || !reg2 || !reg3)
		return (process->carry = 0);
	*reg3 = *reg1 ^ *reg2;
	return (process->carry = 1);
}

int add (t_process *process, int *reg1, int *reg2, int *reg3)
{
	if (!reg1 || !reg2 || !reg3)
		return (process->carry = 0);
	*reg3 = *reg1 + *reg2;
	return (process->carry = 1);
}

int sub (t_process *process, int *reg1, int *reg2, int *reg3)
{
	if (!reg1 || !reg2 || !reg3)
		return (process->carry = 0);
    *reg3 = *reg1 - *reg2;
	return (process->carry = 1);
}