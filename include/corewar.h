/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by mfonteni          #+#    #+#             */
/*   Updated: 2018/05/31 16:42:42 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
#define COREWAR_H

#include "../libft/includes/libft.h"
#include "op.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

/********************DEBUG KINGDOM*********************/
#define ERROR(message) ft_printf("{RED}%s{EOC}", message)


/******************************************************/

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
	int					cycles_left;
	struct s_process	*next;
}						t_process;

typedef struct			s_vm
{
	int					dump;
	int					processes_nbr;
	int					cycle;
	unsigned char		*map;
	struct s_champ		*champ;
	struct s_process	*processes;
}						t_vm;

typedef struct			s_param
{
	int					value;
	int					type;
}						t_param;

typedef struct			s_instr
{
	t_vm				*vm;
	t_process			*process;
	t_param				*params;
}						t_instr;

//free.c
t_vm					*free_vm(t_vm *vm);
t_champ					*rec_free_champs(t_champ *champs);

//init_champs.c
int						init_champs(int ac, char **av, t_vm *vm);

//init.c
t_vm					*init_vm(int argc, char **argv);
int						sort_champs(t_vm *vm);

//get_champ.c
t_champ					*parse_champ(char *file_name , t_champ *champ);
int						fill_id_champs(t_vm *vm);

//error.c
int						usage(int ret);
t_champ					*error_file(char *str, char *file, t_champ *champ);
int						error_mall(int err);
int 					illegal_opt(char *opt, int ret);
int						check_num(t_champ *ch, int num);

//getters.c
t_champ					*get_champ_by_num(t_champ *list, int num);

//process.c
int						add_process(t_vm *vm, int pc, int id);

//option.c
int						known_opt(char *opt);
int						is_opt(char *opt, char *nbr, t_vm *vm, int *ch_num);

//instr_params.c
t_param					*decode_param_type(unsigned char ocp);
t_param					*get_params(t_vm *vm, t_process *process);
int						continue_process(t_vm *vm, t_process *process);

#endif