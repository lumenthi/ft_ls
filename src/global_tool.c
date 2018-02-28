/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:05:35 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/22 14:13:42 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*make_path(char *path, char *str)
{
	char	*new_path;

	new_path = (char*)ft_strnew(ft_strlen(path) + ft_strlen(str) + 2);
	new_path = ft_strcpy(new_path, path);
	new_path = ft_strcat(new_path, "/");
	new_path = ft_strcat(new_path, str);
	return (new_path);
}

char	*get_path(char *arg)
{
	char *path;

	if (!arg)
		return (NULL);
	if (arg[0] == '/')
		return (path = ft_strdup(arg));
	path = make_path(".", arg);
	return (path);
}

void	file_del(t_file **files)
{
	t_file *tmp;

	tmp = NULL;
	if (!(*files))
		return ;
	while ((*files)->next)
	{
		tmp = (*files)->next;
		if ((*files) && (*files)->name)
			free((*files)->name);
		if ((*files) && (*files)->link_name)
			free((*files)->link_name);
		if ((*files) && (*files)->size)
			free((*files)->size);
		if ((*files) && (*files)->owner)
			free((*files)->owner);
		if ((*files) && (*files)->group)
			free((*files)->group);
		free((*files));
		(*files) = tmp;
	}
	free(tmp);
}

int		path_maker(char **argv, int *i, char **path, int argc)
{
	while (argv[*i] == NULL)
		(*i)++;
	if (*i == argc)
		return (1);
	if (argv[*i][0] != '/' && ft_strcmp(argv[*i], "") != 0)
		*path = make_path(".", argv[*i]);
	else
		*path = ft_strdup(argv[*i]);
	return (0);
}

void	error_init(int *error, int *args_er)
{
	*error = 0;
	*args_er = 0;
}
