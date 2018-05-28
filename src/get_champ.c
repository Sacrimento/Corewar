/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 10:35:19 by abouvero          #+#    #+#             */
/*   Updated: 2018/05/28 13:36:31 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static int		get_b_size(unsigned char *b_size)
{
	unsigned int	size;
	int 			i;

	i = -1;
	size = 0;
	while (++i < 4)
	{
		size |= b_size[i];
		size <<= 8;
	}
	return (size >> 8);
}

static int		check_magic(int fd)
{
	unsigned char	magic[4];
	int				i;

	i = -1;
	if (read(fd, magic, 4) != 4)
		return (0);
	while (++i < 4)
		if (((COREWAR_EXEC_MAGIC >> (i * 8)) & 0x000000FF) != magic[3 - i])
			return (0);
	return (1);
}

static int		fill_header(int fd, t_champ *champ)
{
	unsigned char	size_b[4];

	if (read(fd, champ->name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		return (0);
	read(fd, size_b, 4); //MAGIC TRICK
	if (read(fd, size_b, 4) != 4)
		return (0);
	champ->size = get_b_size(size_b);
	ft_printf("SIZE : %d\n", champ->size);
	if (read(fd, champ->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		return (0);
	return (1);
}

t_champ		*parse_champ(char *file_name , t_champ *champ)
{
	int		fd;

	if (!(fd = open(file_name, O_RDONLY)) || fd < 0)
		return (error_file("Le ficher %s n'a pas pu etre ouvert\n", file_name));
	if (!(check_magic(fd)) || !fill_header(fd, champ))
		return (error_file("Le header du fichier %s est invalide\n", file_name));
	if (champ->size > CHAMP_MAX_SIZE)
		return (ft_printf("Le fichier %s est trop gros : %d bytes au lieu de %d bytes\n", file_name, champ->size, CHAMP_MAX_SIZE) ? NULL : NULL);
	if (!(champ->code = (unsigned char *)ft_memalloc(sizeof(char) * champ->size)) || read(fd, champ->code, champ->size) != champ->size)
		return (NULL);
	if (close(fd))
		return (error_file("Le fichier %s n'a pu etre ferme\n", file_name));
	return (champ);
}