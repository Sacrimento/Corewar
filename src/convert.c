/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/13 16:29:54 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

//TODO: test if unsigned long is valid with all cases
int	byte_to_int(unsigned char *map, int cursor, int amount_of_bytes)
{
	int	ret;
	int	i;

	i = -1;
	ret = 0;
	while (++i < amount_of_bytes)
		ret = (ret << 8) | map[get_address(cursor + i)];
	ft_printf("{GREEN}ret %d{EOC}", ret);
	return (ret);
}

int get_address(int value)
{
	if (value < 0)
		value = MEM_SIZE + (value % MEM_SIZE);
	return (value % MEM_SIZE);
}

int	int_to_bytes(int n, int cursor, unsigned char *map)
{
	if (!map)
		return (0);
	map[get_address(cursor + 3)] = (unsigned char) (n & 0x000000FF);
    map[get_address(cursor + 2)] = (unsigned char)((n & 0x0000FF00) >> 8);
    map[get_address(cursor + 1)] = (unsigned char)((n & 0x00FF0000) >> 16);
    map[get_address(cursor + 0)] = (unsigned char)((n & 0xff000000) >> 24);
	return (1);
}
