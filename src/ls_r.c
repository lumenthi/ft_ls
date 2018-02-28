/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_r.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 14:00:40 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/23 11:33:34 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_path(char **path, t_file *files)
{
	char	*new_path;
	int		root;

	root = ft_strncmp(*path, "././", 4);
	new_path = (char*)ft_strnew(ft_strlen(*path) + ft_strlen(files->name) + 2);
	new_path = ft_strcpy(new_path, *path);
	if (ft_strcmp(*path, "./") != 0 && ft_strcmp(*path, "/") != 0)
		new_path = ft_strcat(new_path, "/");
	new_path = ft_strcat(new_path, files->name);
	*path = NULL;
	*path = ft_realloc(*path, ft_strlen(new_path) + 1);
	*path = ft_strcpy(*path, new_path);
	root ? ft_putstr(*path) : ft_putstr(*path + 2);
	ft_putendl(":");
	free(new_path);
}

void	r_print(char *args, t_file *files, char *path)
{
	char	*tmp;
	t_file	*tmp2;

	tmp = ft_strdup(path);
	while (files && files->next)
	{
		if (S_ISDIR(files->perm) && ft_strcmp(files->name, ".") != 0
		&& ft_strcmp(files->name, "..") != 0)
		{
			tmp2 = NULL;
			ft_putchar('\n');
			print_path(&path, files);
			apply_args(args, &tmp2, path);
			r_print(args, tmp2, path);
			file_del(&tmp2);
			free(path);
		}
		path = tmp;
		files = files->next;
	}
	free(tmp);
}
