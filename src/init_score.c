/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/22 17:23:44 by rkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

WINDOW  *init_score(t_visu *visu)
{
	WINDOW  *score;
	
	(void)visu;
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	initscr();
	curs_set(0);
	score = subwin(stdscr, LINES - 13 , COLS * 0.2, 6, COLS * 0.7);
	wbkgd(score, COLOR_PAIR(1));
	refresh();
	return (score);
}
