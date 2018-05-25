/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 10:35:19 by abouvero          #+#    #+#             */
/*   Updated: 2018/05/25 15:46:23 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int 	check_magic(int fd)
{
	int				ret;
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

int		fill_header(int fd/*, t_champ *champ*/)
{
	if (read(fd, champ->name, PROG_NAME_LENGTH + 1) != PROG_NAME_LENGTH + 1)
		return (0);
	if (read(fd, champ->size, 4) != 4)
		return (0);
	if (read(fd, champ->comment, COMMENT_LENGTH + 1) != COMMENTLENGTH + 1)
		return (0);
	
}

t_champ		*parse_champ(char *file_name , t_champs *champ)
{
	int		fd;

	if (!(fd = open(file_name, O_RDONLY)) || fd < 0)
		return 0;//(error_file("Le ficher %s n'a pas pu etre ouvert\n", file_name, 0));
	if (!(check_magic(fd)) || !fill_header(fd, champ))
		return 0;//(error_file("Le header du fichier %s est invalide\n", file_name, 0));
	if (!(champ->code = (unsigned char *)ft_memalloc(sizeof(char) * champ->size))) || read(fd, champ->code, champ->size) != champ->size)
		return (error_mall(0));
	if (!(close(fd)))
		return 0;//(error_file("Le fichier %s n'a pu etre ferme\n", file_name, 0));
	return (champ);
}