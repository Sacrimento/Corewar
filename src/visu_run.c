/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 16:24:18 by rkrief            #+#    #+#             */
/*   Updated: 2018/06/22 16:23:15 by rkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

void	print_header(WINDOW *win)
{
	int	x_offset;

	x_offset = 70;
	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 1, x_offset, HEADER_LINE_1);
	mvwprintw(win, 2, x_offset, HEADER_LINE_2);
	mvwprintw(win, 3, x_offset, HEADER_LINE_3);
	mvwprintw(win, 4, x_offset, HEADER_LINE_4);
	mvwprintw(win, 5, x_offset, HEADER_LINE_5);
	wattroff(win, COLOR_PAIR(1));
	wrefresh(win);
}

void	visu_run(t_vm vm, WINDOW *win, t_visu *visu, WINDOW *score, WINDOW *test, int start)
{
	int ch;
	int j;
	int *pc;
	int	n;
	int pcx;
	int pcy;
	int x;
	int y;
	t_process *pro;
	t_champ *champ;

	j = 0;
	x = 5;
	y = 7;
	n = 0;
	print_header(win);
	if (!(pc = (int*)ft_memalloc(sizeof(int) * (vm.processes_nbr))))
		exit (0);
	pro = vm.processes;
	//ft_putchar(' ');
//	ft_putnbr(vm.processes_nbr);
//	ft_putchar(' ');
	while (n < vm.processes_nbr)
	{
		pc[n] = vm.processes->pc;
//		wprintw(test, "- %d -", pc[n]);
		vm.processes = vm.processes->next;
		n++;
	}
	vm.processes = pro;
	nodelay(stdscr,TRUE);
//	else
//		nodelay(stdscr,FALSE);
	ch = getch();
	if (ch == 100)
	{
		if (visu->slow > 0)
			visu->slow = visu->slow - 3000;
	}
	if (ch == 115)
		visu->slow = visu->slow + 3000;
	if (ch == 3)
	{
		clear();
		exit (0);
	}
	if (ch == 32)
	{
		mvwprintw(score, 1, 5, "***PAUSED***");
		wrefresh(score);
		nodelay(stdscr, FALSE);
		while (ch != 112)
			ch = getch();
	}
	if (ch == 114)
		visu->slow = 300000;
	if (ch == 116)
		visu->slow = 0;
	if (ch == 49)
	{
		while (ch != 49)
			ch = getch();
	}
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	wattron(score, COLOR_PAIR(7));
	box(score, ACS_VLINE, ACS_HLINE);
	mvwprintw(score, 1, 5, "**RUNNING***");
	mvwprintw(score, 3, 5, "Cycle number : %d\n", vm.tt_cycle);
	mvwprintw(score, 5, 5, "nbr processus: %d\n", vm.processes_nbr);
	mvwprintw(score, 7, 5, "Delay :  %d\n", visu->slow);
	champ = vm.champ;
	n = 1;
	int k;
	k = 2;
	while (vm.champ)
	{	
		wattron(score, COLOR_PAIR(7));
		mvwprintw(score, 7 + k, 5, "Player %d name: ", n);
		mvwprintw(score, 9 + k, 5, "Current lives: ");
		wattroff(score, COLOR_PAIR(7));
		wattron(score, COLOR_PAIR(n));
		mvwprintw(score, 7 + k, 26, "%s", vm.champ->name);
		mvwprintw(score, 9 + k, 26, "%d", vm.champ->lives);
		k += 8;
		vm.champ = vm.champ->next;
		n++;
	}
	vm.champ = champ;
	wattroff(score, COLOR_PAIR(7));
	while (j < MEM_SIZE)
	{

		wattron(win, COLOR_PAIR(vm.colors_map[j]));
		mvwprintw(win, y, x, "%.2x", vm.map[j++]);
		x += 2;
		if (!(j % 64) && j != 0){
			mvwprintw(win, y, x, "\n"); x = 5, y++;}
		else{
			mvwprintw(win, y, x, " ");x++;}
		wattroff(win, COLOR_PAIR(vm.colors_map[j - 1]));
	}
	n = 0;
	(void)test;
	attron(A_STANDOUT);
	while (n < vm.processes_nbr)
	{
		pcx = 5 + (pc[n] * 3);
		pcy = 7;
		if ((pc[n] >= 64) && pc[n] != 0)
		{
			pcx = 5 + ((pc[n] % 64) * 3);
			pcy = 7 + (pc[n] / 64);
		}
		mvprintw(pcy, pcx, "%.2x", vm.map[pc[n]]);
		n++;
	}
	n = 0;
	attroff(A_STANDOUT);
	wattron(score, COLOR_PAIR(7));
	box(score, ACS_VLINE, ACS_HLINE);
	wattroff(score, COLOR_PAIR(7));
	wrefresh(win);
	wrefresh(score);
	if (!start)
		nodelay(stdscr,FALSE);
		ch = getch();
	usleep(visu->slow);
}
