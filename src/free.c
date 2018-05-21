/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:14:11 by abouvero          #+#    #+#             */
/*   Updated: 2018/05/21 13:03:09 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	rec_free_champs(t_champs *champs)
{
	if (!champs)
		return ;
	if (champs->next)
		rec_free_champs(champs->next);
	ft_memdel((void**)&champs);
}

void	rec_free_processes(t_processes *processes)
{
	if (!processes)
		return ;
	if (processes->next)
		rec_free_processes(processes->next);
	ft_memdel((void**)&processes);
}

int		free_vm(t_vm *vm)
{
	if (!vm)
		return ;
	if (vm->map)
		ft_memdel((void**)&vm->map);
	if (vm->champs)
		rec_free_champs(vm->champs);
	if (vm->processes)
		rec_free_processes(vm->processes);
	ft_memdel((void**)&vm);
	return (1);
}