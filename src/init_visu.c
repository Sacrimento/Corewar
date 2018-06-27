/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 16:21:02 by rkrief            #+#    #+#             */
/*   Updated: 2018/06/27 14:52:57 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

WINDOW	*init_visu()
{
	WINDOW	*win;

	initscr();
	noecho();
	curs_set(0);
	start_color();
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
	win = subwin(stdscr, LINES, COLS * 0.7, 0, 0);
	wbkgd(win, COLOR_PAIR(3));
	refresh();
	return (win);
}
