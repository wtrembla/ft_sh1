/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 19:10:27 by wtrembla          #+#    #+#             */
/*   Updated: 2014/04/25 19:45:44 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

static int		var_isvalid(char *var, char **env)
{
	int		i;

	i = 0;
	if (ft_strchr(var, '='))
	{
		ft_putendl_fd("setenv: syntax error", 2);
		return (0);
	}
	else
	{
		while (env && env[i])
		{
			if (!ft_strncmp(var, env[i], ft_strlen(var)))
			{
				ft_putendl_fd("setenv: variable already exits", 2);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

static void		add_var(char **av, t_env **env)
{
	char	**senv;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*env)->env && (*env)->env[i])
		i++;
	if (!(senv = (char **)malloc(sizeof(char *) * (i + 2))))
	{
		ft_putendl_fd("add_var: memory allocation failed", 2);
		return ;
	}
	while ((*env)->env && (*env)->env[j])
	{
		senv[j] = ft_strdup((*env)->env[j]);
		j++;
	}
	tmp = ft_strjoin(av[1], "=");
	senv[j] = av[2] != NULL ? ft_strjoin(tmp, av[2]) : ft_strdup(tmp);
	ft_strdel(&tmp);
	senv[++j] = NULL;
	del_av((*env)->env);
	(*env)->env = senv;
}

void			apply_setenv(char *command)
{
	char	**av;
	int		size;
	t_env	*env;

	av = ft_strsplit(command, ' ');
	size = av_size(av);
	env = init_env(NULL);
	if (size == 1)
		apply_env(command);
	else if (size > 3)
		ft_putendl_fd("setenv: too many arguments", 2);
	else
	{
		if (var_isvalid(av[1], env->env))
			add_var(av, &env);
	}
	del_av(av);
}
