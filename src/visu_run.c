/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 16:24:18 by rkrief            #+#    #+#             */
/*   Updated: 2018/06/22 12:53:46 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

void	visu_run(t_vm *vm, WINDOW *win, t_visu *visu)
{
	int ch;
	int j;
	int pc;
	int pcx;
	int pcy;
	unsigned char pchar;

	j = 0;
	visu->slow = 0;
	pc = vm->processes->pc;
	nodelay(stdscr,TRUE);
	ch = getch();
	if (ch == 95)
		visu->slow = visu->slow - 1000;
	if (ch == 43)
		visu->slow = visu->slow + 1000;
	if (visu->slow <= 0)
		visu->slow = 3000;
	if (ch == 3)
	{
		clear();
		exit (0);
	}
	if (ch == 45)
		visu->slow = 2000;
	if (ch == 49)
	{	
		while (ch != 49)
			ch = getch();
	}
	mvwprintw(win, 0, 0, "cycle numero : %d\n", vm->tt_cycle);
	while (j < MEM_SIZE)
	{
		wprintw(win, "%.2x", vm->map[j++]);
		if (!(j % 64) && j != 0)
			wprintw(win, "\n");
		else
			wprintw(win, " ");
	}
	pcx = 20 + (pc * 3);
	pcy = 2;
	if ((pc >= 64) && pc != 0)
	{
		pcx = 20 + ((pc % 64) * 3);
		pcy = 2 + (pc / 64);
	}
	pchar = vm->map[pc];
	attron(A_STANDOUT);
	mvprintw(pcy, pcx, "%.2x", vm->map[pc]);
	attroff(A_STANDOUT);
	usleep(visu->slow);
	wrefresh(win);
}
