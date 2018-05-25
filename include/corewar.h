/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by mfonteni          #+#    #+#             */
/*   Updated: 2018/05/25 17:13:46 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __COREWAR_H__
#define __COREWAR_H__

#include "../libft/includes/libft.h"
#include "op.h"
#include <fcntl.h>

typedef struct	s_champ
{
	int				id;
	int				size;
	int				lives;
	char 			name[PROG_NAME_LENGTH + 1];
	char 			comment[COMMENT_LENGTH + 1];
	unsigned char	*code;
	struct s_champ	*next;
}				t_champ;

typedef struct	s_process
{
	int					alive;
	int					pc;
	int					carry;
	int					reg[REG_SIZE];
	unsigned char		*start;
	struct s_process	*next;
}				t_process;

typedef struct	s_vm
{
	int					opt;
	int					processes_nbr;
	int					cycle;
	int					display_live;
	unsigned char		*map;
	struct s_champ		*champ;
	struct s_process	*processes;
}				t_vm;

typedef struct	s_instr
{
	int value;
	int *adress;
}				t_instr;



//free.c
int				free_vm(t_vm *vm);

//init_champs.c
t_champ			*init_champs(int ac, char **av);

//get_champ.c
t_champ		*parse_champ(char *file_name , t_champ *champ);

//error.c
int				usage(void);
int				error_file(char *str, char *file, int ret);
int				error_mall(int err);

//getters.c
t_champ			*get_champ_by_num(t_champ *list, int num);


#endif