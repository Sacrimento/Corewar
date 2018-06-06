/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/06 12:47:26 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static void			winner(t_champ *ch)
{

	if (ch)
		ft_printf("le joueur %d(%s) a gagne\n", ch->id, ch->name);
	else
		ft_printf("Les joueurs n'ont pas pu se departager, egalite !\n");
}

int					main(int argc, char **argv)
{
	t_vm	*vm;

	if (argc < 2)
		return (usage(1));
	if (!check_inputs())
		return (1);
	if (!(vm = init_vm(argc, argv)))
		return (1);
	//run(vm);
	winner(vm->last);
	free_vm(vm);
	return (0);
}
