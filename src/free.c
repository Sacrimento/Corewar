/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:14:11 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/26 13:19:28 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int		free_visu(t_visu *visu)
{
	ft_memdel((void**)&visu);
	return (1);
}

t_champ	*rec_free_champs(t_champ *champs)
{
	if (!champs)
		return (NULL);
	if (champs->next)
		rec_free_champs(champs->next);
	ft_memdel((void**)&champs->code);
	ft_memdel((void**)&champs);
	return (NULL);
}

void	rec_free_processes(t_process *processes)
{
	if (!processes)
		return ;
	if (processes->next)
		rec_free_processes(processes->next);
	ft_memdel((void**)&processes);
}

t_vm	*free_vm(t_vm *vm)
{
	if (!vm)
		return (NULL);
	if (vm->map)
		ft_memdel((void**)&vm->map);
	if (vm->champ)
		rec_free_champs(vm->champ);
	if (vm->processes)
		rec_free_processes(vm->processes);
	if (vm->colors_map)
		ft_memdel((void**)&vm->colors_map);
	ft_memdel((void**)&vm);
	return (0);
}
