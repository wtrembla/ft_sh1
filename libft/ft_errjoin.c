/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/31 16:03:50 by wtrembla          #+#    #+#             */
/*   Updated: 2014/02/03 15:31:51 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_errjoin(char *str1, char *str2)
{
	char	*join;

	join = ft_strjoin(str1, str2);
	ft_putendl_fd(join, 2);
	ft_strdel(&join);
	exit(0);
}
