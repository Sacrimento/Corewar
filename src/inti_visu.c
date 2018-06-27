/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inti_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:45:08 by rkrief            #+#    #+#             */
/*   Updated: 2018/06/26 15:57:37 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

t_visu *inti_visu(void)
{
	t_visu *visu;

	if (!(visu = ft_memalloc(sizeof(t_visu))))
		return (NULL);
	visu->start = 0;
	visu->win = init_visu(visu);
	visu->score = init_score(visu);
	visu->slow = 30000;
	return (visu);
}