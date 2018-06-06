/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 11:12:03 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/06 11:15:43 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int		known_opt(char *opt)
{
	if (!ft_strcmp(opt, "-n") || !ft_strcmp(opt, "-dump"))
		return (1);
	return (0);
}

int		check_inputs(void)
{
	if (0)
		ft_dprintf(2, "Invalid values in \"op.h\"\n");
	return (1);
}

int		list_length(t_champ *champ)
{
	return (champ ? 1 + list_length(champ->next) : 0);
}
