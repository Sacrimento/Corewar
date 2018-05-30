/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by mfonteni          #+#    #+#             */
/*   Updated: 2018/05/30 16:21:52 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
#define COREWAR_H

#include "../libft/includes/libft.h"
#include "op.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct			s_op
{
	char				*name;
	int					nb_param;
	int					type_param[MAX_ARGS_NUMBER];
	int					opcode;
	int					nb_cycle;
	char				*desc;
	int					instr: 2;
	int					oct: 2;
}						t_op;

typedef struct			s_champ
{
	int					id;
	int					size;
	int					lives;
	char 				name[PROG_NAME_LENGTH + 1];
	char 				comment[COMMENT_LENGTH + 1];
	unsigned char		*code;
	struct s_champ		*next;
}						t_champ;

typedef struct			s_process
{
	int					alive;
	int					pc;
	int					carry;
	int					to_wait;
	int					reg[REG_NUMBER];
	struct s_process	*next;
}						t_process;

typedef struct			s_vm
{
	int					opt;
	int					processes_nbr;
	int					cycle;
	unsigned char		*map;
	struct s_champ		*champ;
	struct s_process	*processes;
}						t_vm;

typedef struct			s_param_instr
{
	int					value;
	void				*address;
	int					type;
}						t_param_instr;

typedef struct			s_instr
{
	t_process			*process;
	int					opcode;
	t_param_instr		params[3];
	int					cycles_left;
}						t_instr;

//free.c
t_vm					*free_vm(t_vm *vm);
t_champ					*rec_free_champs(t_champ *champs);

//init_champs.c
int						init_champs(int ac, char **av, t_vm *vm);

//init.c
t_vm					*init_vm(int argc, char **argv);

//get_champ.c
t_champ					*parse_champ(char *file_name , t_champ *champ);

//error.c
int						usage(void);
t_champ					*error_file(char *str, char *file, t_champ *champ);
int						error_mall(int err);

//getters.c
t_champ					*get_champ_by_num(t_champ *list, int num);

//process.c
int						add_process(t_vm *vm, int pc, int id);

#endif