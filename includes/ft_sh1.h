/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 13:56:53 by wtrembla          #+#    #+#             */
/*   Updated: 2014/04/24 20:16:48 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_H
# define FT_SH1_H

/*
** include
*/
# include "get_next_line.h"
# include "libft.h"

/*
** define
*/
# define BUILT_NUM 5

/*
** typedef
*/

typedef struct	s_built
{
	char		*name;
	void		(*apply_built)(char *);
}				t_built;

typedef struct	s_env
{
	char		**env;
	char		**path;
	char		*pwd;
	char		*oldpwd;
	char		*home;
}				t_env;

typedef struct	s_id
{
	int			id;
	pid_t		child;
	pid_t		father;
	int			built;
}				t_id;

/*
** global
*/
t_id			g_pid;

/*
** built_cd.c
*/
void			apply_cd(char *command);

/*
** built_env.c
*/
void			apply_env(char *command);

/*
** built_exit.c
*/
void			apply_exit(char *command);

/*
** built_setenv.c
*/
void			apply_setenv(char *command);

/*
** built_unsetenv.c
*/
void			apply_unsetenv(char *command);

/*
** builtins.c
*/
int				check_builtin(char *command);
void			del_builtin(void);
t_built			*init_builtin(void);

/*
** command_fct.c
*/
void			command_proc(char *command);

/*
** environ_fct.c
*/
char			**copy_env(char **environ);
char			*copy_home(char **environ);
char			*copy_oldpwd(char **environ);
char			**copy_path(char **environ);
char			*copy_pwd(char **environ);

/*
** main.c
*/
void			del_env(void);
void			display_prompt(void);
t_env			*init_env(char **environ);

/*
** minishell.c
*/
int				av_size(char **av);
void			del_av(char **av);
void			minishell(void);

/*
** path_fct.c
*/
char			*build_path(char *path, char *command);
int				check_path(char *path);

/*
** signal_fct.c
*/
void			catch_signal(void);
void			init_pid(void);

#endif
