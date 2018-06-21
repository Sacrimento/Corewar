/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrief <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 16:21:02 by rkrief            #+#    #+#             */
/*   Updated: 2018/06/20 16:35:25 by rkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

WINDOW	*init_visu(t_visu *visu)
{
	WINDOW	*win;

	initscr();
	curs_set(0);
	visu->height = 65;
	visu->width = 65 * 3;
	visu->start_y = 1;
	visu->start_x = 20;
	win = newwin(visu->height, visu->width, visu->start_y, visu->start_x);
	wrefresh(win);
	return (win);
}
