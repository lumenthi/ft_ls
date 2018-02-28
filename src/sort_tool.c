/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 12:25:17 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/23 10:55:59 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ferror(t_file *file, char **new_path, t_stat **stats)
{
	if (file->link_name)
	{
		if (lstat(*new_path, *stats) == -1)
		{
			free(*new_path);
			return (0);
		}
	}
	else
	{
		if (stat(*new_path, *stats) == -1)
		{
			free(*new_path);
			return (0);
		}
	}
	return (1);
}

char	*sp_si(int str1, int str2)
{
	char *tmp;
	char *s1;
	char *s2;
	char *ret;

	s1 = ft_itoa(str1);
	s2 = ft_itoa(str2);
	tmp = ft_strjoin(s1, ", ");
	ret = ft_strjoin(tmp, s2);
	free(tmp);
	free(s1);
	free(s2);
	return (ret);
}

int		lst_len(t_file *file)
{
	int		nb;
	t_file	*tmp;

	nb = 0;
	if (!file)
		return (0);
	tmp = file;
	while (tmp->next && tmp)
	{
		nb++;
		tmp = tmp->next;
	}
	return (nb);
}
