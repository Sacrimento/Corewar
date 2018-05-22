/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by mfonteni          #+#    #+#             */
/*   Updated: 2018/05/22 13:48:11 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int		main(int argc, char **argv)
{
	t_vm	*vm;
	int 	opt;

	if ((opt = set_opt(argc, argv)) == -1 || check_inputs(argc, argv))
		return (1);
	if (!(vm = init_vm(argc, argv, opt)))
		return (free_vm(vm));
	free_vm(vm);
	return (0);
}