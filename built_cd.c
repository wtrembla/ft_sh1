/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/24 15:29:45 by wtrembla          #+#    #+#             */
/*   Updated: 2014/04/30 19:04:20 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

static void		improper_path(int ret, char *path)
{
	if (ret == -1)
		ft_putjoin_fd("cd: no such file or directory: ", path, 2);
	else if (ret == -2)
		ft_putjoin_fd("cd: permission denied: ", path, 2);
}

static char		*get_newdir(t_env *env, char *av)
{
	char	*new_dir;
	char	*tmp;

	if (!ft_strncmp(av, "./", 2))
		new_dir = ft_strjoin(env->pwd, ft_strchr(av, '/'));
	else if (av[0] == '/')
		new_dir = ft_strdup(av);
	else if (!ft_strcmp(av, "-"))
		new_dir = ft_strdup(env->oldpwd);
	else if (!ft_strcmp(av, ".."))
		new_dir = ft_strlen(env->pwd) - ft_strlen(ft_strrchr(env->pwd, '/')) ?
				ft_strndup(env->pwd, ft_strlen(env->pwd)
							- ft_strlen(ft_strrchr(env->pwd, '/')) - 1)
				: ft_strdup("/");
	else
	{
		tmp = env->pwd[ft_strlen(env->pwd) - 1] != '/' ?
			ft_strjoin(env->pwd, "/") : NULL;
		new_dir = tmp != NULL ? ft_strjoin(tmp, av) : ft_strjoin(env->pwd, av);
		ft_strdel(&tmp);
	}
	return (new_dir);
}

static int		update_var(t_env **env, char *var, char *value)
{
	int		i;

	i = 0;
	while ((*env)->env && (*env)->env[i]
			&& ft_strncmp((*env)->env[i], var, ft_strlen(var)))
		i++;
	if ((*env)->env[i])
	{
		ft_strdel(&(*env)->env[i]);
		(*env)->env[i] = ft_strjoin(var, value);
		return (1);
	}
	return (0);
}

static void		update_env(t_env **env, char *new_dir)
{
	char	*tmp;

	ft_strdel(&(*env)->oldpwd);
	(*env)->oldpwd = (*env)->pwd;
	if (ft_strstr(new_dir, "/nfs/"))
		(*env)->pwd = ft_strdup(ft_strstr(new_dir, "/nfs/"));
	else
		(*env)->pwd = ft_strdup(new_dir);
	if (!(update_var(env, "PWD=", (*env)->pwd)))
	{
		tmp = ft_strjoin("setenv PWD ", (*env)->pwd);
		apply_setenv(tmp);
		ft_strdel(&tmp);
	}
	if (!(update_var(env, "OLDPWD=", (*env)->oldpwd)))
	{
		tmp = ft_strjoin("setenv OLDPWD ", (*env)->oldpwd);
		apply_setenv(tmp);
		ft_strdel(&tmp);
	}
}

void			apply_cd(char *command)
{
	char	**av;
	char	*new_dir;
	int		ret;
	int		size;
	t_env	*env;

	ret = 0;
	av = ft_strsplit(command, ' ');
	new_dir = NULL;
	size = av_size(av);
	env = init_env(NULL);
	if (size > 2)
		ft_putendl_fd("cd: syntax error", 2);
	else if (size == 1 || (size == 2 && !ft_strcmp(av[1], "~")))
		new_dir = ft_strdup(env->home);
	else
		new_dir = get_newdir(env, av[1]);
	if (new_dir && !(ret = check_path(new_dir)) && !chdir(new_dir))
		update_env(&env, new_dir);
	else if (new_dir && !(ret = check_path(new_dir)) && chdir(new_dir) == -1)
		ft_putjoin_fd("cd: not a directory: ", av[1], 2);
	if (new_dir && ret && av[1])
		improper_path(ret, av[1]);
	ft_strdel(&new_dir);
	del_av(av);
}
