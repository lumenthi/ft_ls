/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 11:05:24 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/27 12:12:53 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_ls_init(t_file **files, int *check, int i)
{
	*files = NULL;
	*check = i;
}

void	separate(char *full, char **path, char **single)
{
	char *tmp;
	char *tmp2;
	char *sep;

	tmp = ft_strdup(full);
	tmp2 = ft_strdup(full);
	*single = ft_strdup(ft_strrchr(tmp, '/') + 1);
	sep = ft_strrchr(tmp2, '/');
	*(sep + 1) = '\0';
	*path = ft_strdup(tmp2);
	free(tmp);
	free(tmp2);
}

int		is_sym(char **p)
{
	DIR		*dir;
	char	*path;
	char	*single;
	t_dir	*content;

	separate(*p, &path, &single);
	if (!(dir = opendir(path)))
		return (0);
	while ((content = readdir(dir)))
	{
		if (ft_strcmp(content->d_name, single) == 0)
			break ;
	}
	free(path);
	free(single);
	if (closedir(dir) == -1)
		print_error(path, errno, 0);
	if (content)
		return (content->d_type == DT_LNK ? 1 : 0);
	return (0);
}

void	ls_print(t_file *files)
{
	if (!files)
		return ;
	while (files->next)
	{
		if (files)
			ft_putendl(files->name);
		files = files->next;
	}
}
