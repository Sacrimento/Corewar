/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by mfonteni          #+#    #+#             */
/*   Updated: 2018/05/25 16:52:57 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int			check_inputs(int argc, char **argv)
{
	//Check des defsines d'op.h
	return (0);
}

static int	list_length(t_champ *champ)
{
	return (champ ? 1 + list_length(champ->next) : 0);
}

t_vm		*init_vm(int argc, char **argv)
{
	t_vm		*vm;
	int			opt;
	t_champ		*champs;

	champs = NULL;
	if (!(champs = init_champs(argc, argv)))
		return (0); //Pas forcement malloc
	if (!(vm = (t_vm*)ft_memalloc(sizeof(t_vm))))
		return (error_mall(0));
	if (!(vm->map = (unsigned char *)ft_memalloc(MEM_SIZE)))
		return (error_mall(0));
	vm->opt = opt;
	vm->processes_nbr = 0;
	vm->cycle = 0;
	vm->champ = champs;
	vm->processes= NULL;
	if (!load_champs(vm), list_length(vm->champ));
	return (vm);
}