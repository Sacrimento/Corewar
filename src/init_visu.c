/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 16:21:02 by rkrief            #+#    #+#             */
/*   Updated: 2018/06/26 13:09:45 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

WINDOW	*init_visu(void)
{
	WINDOW	*win;

	initscr();
	curs_set(0);
	start_color();
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
	win = subwin(stdscr, LINES, COLS * 0.7, 0, 0);
	wbkgd(win, COLOR_PAIR(3));
	refresh();
	return (win);
}

t_visu	*init_vars_visu(WINDOW *win, WINDOW *score)
{
	t_visu	*visu;

	if (!(visu = (t_visu*)ft_memalloc(sizeof(t_visu))))
		return (NULL);
	visu->start = 0;
	win = init_visu();
	score = init_score(visu);
	visu->slow = 30000;
	return (visu);
}
