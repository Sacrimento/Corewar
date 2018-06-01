/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:36:15 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/01 17:41:54 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

t_champ	*get_champ_by_num(t_champ *list, int num)
{
	t_champ *current;

	if (!list)
		return (NULL);
	current = list;
	while (current && current->id != num)
	{
		ft_printf("%d\n", current->id);
		current = current->next;
	}
	return (current);
}
