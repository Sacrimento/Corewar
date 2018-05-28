/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by mfonteni          #+#    #+#             */
/*   Updated: 2018/05/28 15:42:29 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
#define COREWAR_H
#define REG 10
#define DIRECT 20
#define INDIRECT 30

#include "../libft/includes/libft.h"
#include "op.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

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

typedef struct	s_param_instr
{
	int		value;
	void	*address;
	int		active;
}				t_param_instr;

typedef struct	s_instr
{
	t_process		*process;
	int				opcode;
	t_param_instr	params[3];
	int				cycles_left;
}				t_instr;

//free.c
int				free_vm(t_vm *vm);

//init_champs.c
t_champ			*init_champs(int ac, char **av);

//init.c
t_vm			*init_vm(int argc, char **argv, int opt);

//get_champ.c
t_champ			*parse_champ(char *file_name , t_champ *champ);

//error.c
int				usage(void);
t_champ			*error_file(char *str, char *file);
int				error_mall(int err);

//getters.c
t_champ			*get_champ_by_num(t_champ *list, int num);

#endif