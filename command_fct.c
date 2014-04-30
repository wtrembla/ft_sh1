/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 15:47:16 by wtrembla          #+#    #+#             */
/*   Updated: 2014/04/30 17:11:20 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

static void		improper_command(int ret, char *command)
{
	if (ret == -1 && (!ft_strncmp(command, "./", 2)
					|| !ft_strncmp(command, "../", 3) || command[0] == '/'))
		ft_putjoin_fd("ft_sh1: no such file or directory: ", command, 2);
	else if (ret == -1)
		ft_putjoin_fd("ft_sh1: command not found: ", command, 2);
	else if (ret == -2)
		ft_putjoin_fd("ft_sh1: permission denied: ", command, 2);
}

static char		*check_command(char *command)
{
	char	*tmp;
	int		i;
	int		ret;
	t_env	*env;

	ret = 0;
	env = init_env(NULL);
	tmp = NULL;
	if ((!ft_strncmp(command, "./", 2) || !ft_strncmp(command, "../", 3)
		|| command[0] == '/') && !(ret = check_path(command)))
		return (ft_strdup(command));
	else if (!ret)
	{
		i = -1;
		while (env->path[++i])
		{
			ft_strdel(&tmp);
			tmp = build_path(env->path[i], command);
			if (!(ret = check_path(tmp)))
				return (tmp);
		}
	}
	improper_command(ret, command);
	ft_strdel(&tmp);
	return (NULL);
}

void			command_proc(char *command)
{
	char	**av;
	char	*tmp;

	init_pid();
	av = ft_strsplit(command, ' ');
	if (av && (tmp = check_command(av[0])))
	{
		ft_strdel(&av[0]);
		av[0] = tmp;
		if ((g_pid.father = fork()) == -1)
		{
			del_av(av);
			ft_putendl_fd("command_proc: no child process created", 2);
			return ;
		}
		if (g_pid.father)
			wait(&g_pid.id);
		if (!g_pid.father)
		{
			if (execve(av[0], av, init_env(NULL)->env) == -1)
				ft_putjoin_fd("ft_sh1: command not found: ", av[0], 2);
		}
	}
	del_av(av);
}
