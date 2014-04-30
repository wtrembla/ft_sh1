/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 14:56:23 by wtrembla          #+#    #+#             */
/*   Updated: 2014/04/24 20:02:32 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int		av_size(char **av)
{
	int		i;

	i = 0;
	while (av && av[i])
		i++;
	return (i);
}

void	del_av(char **av)
{
	int		i;

	i = 0;
	if (av)
	{
		while (av[i])
		{
			ft_strdel(&av[i]);
			i++;
		}
		free(av);
		av = NULL;
	}
}

void	minishell(void)
{
	char	*line;
	char	*trim;

	catch_signal();
	while (get_next_line(0, &line))
	{
		trim = ft_strtrim(line);
		if (trim && *trim)
		{
			if (!check_builtin(trim))
				command_proc(trim);
			init_pid();
		}
		ft_strdel(&line);
		ft_strdel(&trim);
		display_prompt();
	}
	apply_exit(NULL);
}
