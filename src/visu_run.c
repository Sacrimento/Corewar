/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 16:24:18 by rkrief            #+#    #+#             */
/*   Updated: 2018/06/25 17:41:50 by rkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

void	print_header(WINDOW *win)
{
	int	x_offset;

	x_offset = 79;
	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 1, x_offset, HEADER_LINE_1);
	mvwprintw(win, 2, x_offset, HEADER_LINE_2);
	wattroff(win, COLOR_PAIR(1));
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, 3, x_offset, HEADER_LINE_3);
	mvwprintw(win, 4, x_offset, HEADER_LINE_4);
	wattroff(win, COLOR_PAIR(2));
	wattron(win, COLOR_PAIR(3));
	mvwprintw(win, 5, x_offset, HEADER_LINE_5);
	wattroff(win, COLOR_PAIR(3));
	wrefresh(win);
}


void	init_pairy(WINDOW *score)
{
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_GREEN);
	init_pair(9, COLOR_BLACK, COLOR_RED);
	init_pair(10,COLOR_BLACK,  COLOR_BLUE);
	init_pair(11, COLOR_BLACK, COLOR_YELLOW);
	init_pair(12, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(13, COLOR_BLACK, COLOR_CYAN);
	init_pair(14, COLOR_BLACK, COLOR_WHITE);
	wattron(score, COLOR_PAIR(7));
	mvwprintw(score, 45, 5, "Press 'Enter' to start");
	mvwprintw(score, 47, 5, "Press 'Space' to pause");
	mvwprintw(score, 49, 5, "Press 'P' to resume");
	mvwprintw(score, 51, 5, "Press 'S' to add delay");
	mvwprintw(score, 53, 5, "Press 'D' to reduce delay");
	mvwprintw(score, 55, 5, "Press 'T' to delete delay");
	mvwprintw(score, 57, 5, "Press 'R' to go step by step");
	wattroff(score, COLOR_PAIR(7));
}

void	visu_run(t_vm vm, WINDOW *win, t_visu *visu, WINDOW *score)
{
	int x;
	int y;
	int k;
	t_champ *champ;

	visu->pos = 0;
	x = 5;
	y = 7;
	visu->ind = 0;
	init_pairy(score);
	print_header(win);
	if (!(visu->pc = (int*)ft_memalloc(sizeof(int) * (vm.processes_nbr))))
		exit (0);
	while (visu->ind < vm.processes_nbr)
	{
		visu->pc[visu->ind] = vm.processes->pc;
		vm.processes = vm.processes->next;
		visu->ind++;
	}
	nodelay(stdscr,TRUE);
	visu->ch = getch();
	if (visu->ch == 100)
	{
		if (visu->slow > 0)
			visu->slow = visu->slow - 3000;
	}
	if (visu->ch == 115)
		visu->slow = visu->slow + 3000;
	if (visu->ch == 3)
	{
		clear();
		exit (0);
	}
	if (visu->ch == 32)
	{
		mvwprintw(score, 1, 5, "***PAUSED***");
		wrefresh(score);
		nodelay(stdscr, FALSE);
		while (visu->ch != 112)
			visu->ch = getch();
	}
	nodelay(stdscr,TRUE);
	if (visu->ch == 114)
		visu->slow = 300000;
	if (visu->ch == 116)
		visu->slow = 0;
	if (visu->ch == 49)
	{
		while (visu->ch != 49)
			visu->ch = getch();
	}
	wattron(score, COLOR_PAIR(7));
	box(score, ACS_VLINE, ACS_HLINE);
	if (!visu->start)
		mvwprintw(score, 1, 5, "***PAUSED***");
	else
		mvwprintw(score, 1, 5, "**RUNNING***");
	mvwprintw(score, 6, 5, "Cycle number : %d\n", vm.tt_cycle);
	mvwprintw(score, 8, 5, "nbr processus: %d\n", vm.processes_nbr);
	mvwprintw(score, 10, 5, "Delay :  %d\n", visu->slow);
	champ = vm.champ;
	visu->ind = 1;
	k = 2;
	while (vm.champ)
	{	
		wattron(score, COLOR_PAIR(7));
		mvwprintw(score, 13 + k, 5, "Player %d name: ", vm.champ->id);
		mvwprintw(score, 15 + k, 5, "Current lives: ");
		wattroff(score, COLOR_PAIR(7));
		wattron(score, COLOR_PAIR(visu->ind));
		mvwprintw(score, 13 + k, 29, "%s", vm.champ->name);
		mvwprintw(score, 15 + k, 29, "%-6d", vm.champ->lives);
		k += 8;
		vm.champ = vm.champ->next;
		visu->ind++;
	}
	vm.champ = champ;
	wattroff(score, COLOR_PAIR(7));
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
	wattron(score, COLOR_PAIR(7));
	box(score, ACS_VLINE, ACS_HLINE);
	wattroff(score, COLOR_PAIR(7));
	wrefresh(win);
	wrefresh(score);
	if (!visu->start)
		nodelay(stdscr,FALSE);
		visu->ch = getch();
	usleep(visu->slow);
	ft_memdel((void**)&visu->pc);
}
