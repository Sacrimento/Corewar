/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_score.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrief <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 14:49:14 by rkrief            #+#    #+#             */
/*   Updated: 2018/06/26 14:51:30 by rkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

void    print_pc(t_visu *visu, t_vm vm)
{
	visu->ind = 0;
	while (visu->ind < vm.processes_nbr)
	{
		visu->pcx = 5 + (visu->pc[visu->ind] * 3);
		visu->pcy = 7;
		if ((visu->pc[visu->ind] >= 64) && visu->pc[visu->ind] != 0)
		{
			visu->pcx = 5 + ((visu->pc[visu->ind] % 64) * 3);
			visu->pcy = 7 + (visu->pc[visu->ind] / 64);
		}
		attron(COLOR_PAIR(vm.colors_map[visu->pc[visu->ind]] + 7));
		mvprintw(visu->pcy, visu->pcx, "%.2x", vm.map[visu->pc[visu->ind]]);
		attroff(COLOR_PAIR(vm.colors_map[visu->pc[visu->ind]] + 7));
		visu->ind++;
	}

}

void    print_map_and_pc(t_visu *visu, WINDOW *win, t_vm vm)
{
	int x;
	int y;

	x = 5;
	y = 7;
	while (visu->pos < MEM_SIZE)
	{
		wattron(win, COLOR_PAIR(vm.colors_map[visu->pos]));
		mvwprintw(win, y, x, "%.2x", vm.map[visu->pos++]);
		x += 2;
		if (!(visu->pos % 64) && visu->pos != 0){
			mvwprintw(win, y, x, "\n"); x = 5, y++;}
		else{
			mvwprintw(win, y, x, " ");x++;}
		wattroff(win, COLOR_PAIR(vm.colors_map[visu->pos - 1]));
	}
	print_pc(visu, vm);
}

void    print_score(t_visu *visu, WINDOW *score, t_vm vm, WINDOW *win)
{
	int k;

	k = 2;
	if (!visu->start)
		mvwprintw(score, 1, 5, "***PAUSED***");
	else
		mvwprintw(score, 1, 5, "**RUNNING***");
	mvwprintw(score, 6, 5, "Cycle number : %d\n", vm.tt_cycle);
	mvwprintw(score, 8, 5, "nbr processus: %d\n", vm.processes_nbr);
	mvwprintw(score, 10, 5, "Delay :  %d\n", visu->slow);
	visu->ind = 1;
	while (vm.champ)
	{
		wattron(score, COLOR_PAIR(7));
		mvwprintw(score, 13 + k, 5, "Player %d name: ", vm.champ->id);
		mvwprintw(score, 15 + k, 5, "Current lives: ");
		wattron(score, COLOR_PAIR(visu->ind));
		mvwprintw(score, 13 + k, 29, "%s", vm.champ->name);
		mvwprintw(score, 15 + k, 29, "%-6d", vm.champ->lives);
		k += 8;
		vm.champ = vm.champ->next;
		visu->ind++;
	}
	wattroff(score, COLOR_PAIR(7));
	print_map_and_pc(visu, win, vm);
}
