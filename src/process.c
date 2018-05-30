/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:22:38 by abouvero          #+#    #+#             */
/*   Updated: 2018/05/30 16:22:36 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int		add_process(t_vm *vm, int pc, int id)
{
	t_process	*pro;
	t_process	*new;

	pro = vm->processes;
	if (!(new = ft_memalloc(sizeof(t_process))))
		return (error_mall(0));
	new->alive = 1;
	new->pc = pc;
	new->carry = 0;
	new->to_wait = 0;
	bzero((void *)new->reg, sizeof(new->reg));
	new->reg[0] = id;
	new->next = NULL;
	vm->processes_nbr += 1;
	if (!pro)
	{
		vm->processes = new;
		return (1);
	}
	while (pro->next)
		pro = pro->next;
	pro->next = new;
	return (1);
}