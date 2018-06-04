/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/04 16:57:43 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	bytetoint(unsigned char *map, int ammount_of_bytes)
{
	if (!map)
		return (0);
	if (ammount_of_bytes == 1)
		return (map[0]);
	if (ammount_of_bytes == 2)
		return (map[0] | (map[1] << 8));
	if (ammount_of_bytes == 4)
		return ((map[0] << 24) | (map[1] << 16) | (map[2] << 8) | map[3]);
	return (0);
}

int	inttobytes(unsigned int n, unsigned char *map)
{
	if (!map)
		return (0);
	map[0] = (n >> 24) & 0xFF;
	map[1] = (n >> 16) & 0xFF;
	map[2] = (n >> 8) & 0xFF;
	map[3] = n & 0xFF;
	return (1);
}
