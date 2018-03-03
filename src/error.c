/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 13:15:39 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/03 11:01:35 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_error(char *o_path, int error, int letter)
{
	ft_putstr("ft_ls: ");
	if (error == USAGE)
	{
		ft_putstr("illegal option -- ");
		ft_putchar(letter);
		ft_putchar('\n');
		ft_putstr("usage: ls [-Ralrt1]");
		ft_putendl(" [file ...]");
		exit(EXIT_FAILURE);
	}
	if (error == EACCES)
		ft_putstr(ft_strrchr(o_path, '/') + 1);
	else if (o_path[0] == '.' && o_path[1] == '/')
		ft_putstr(o_path + 2);
	else
		ft_putstr(o_path);
	ft_putstr(": ");
	ft_putendl(strerror(error));
}

int		invalid_path(char *o_path)
{
	DIR		*dir;

	dir = NULL;
	if (!(dir = opendir(o_path)))
		return (errno);
	(closedir(dir) == -1) ? print_error(o_path, errno, 0) : 1;
	return (0);
}

int		check_error(int error, char *path)
{
	char	*pathbu;
	t_file	*single_file;
	char	*tmp;
	char	*single;

	pathbu = NULL;
	single_file = NULL;
	error = invalid_path(path);
	if (error && error != 20)
	{
		pathbu = ft_strdup(path);
		single = ft_strrchr(path, '/') + 1;
		tmp = ft_strdup(single);
		*single = '\0';
		single_file = file_fill_single(path, tmp);
		if (!single_file || single_file->size == 0)
			print_error(pathbu, error, 0);
		else
			error_del(&single_file);
		file_del(&single_file);
		free(tmp);
		free(pathbu);
	}
	return (error);
}

int		print_all_error(char argc, char **argv, int i)
{
	char	*path;
	int		error;

	path = "";
	error = 0;
	while (i < argc)
	{
		if (argv[i][0] != '/' && ft_strcmp(argv[i], "") != 0)
			path = make_path(".", argv[i]);
		else
			path = ft_strdup(argv[i]);
		if (ft_strcmp(path, "") == 0)
		{
			print_error(path, 2, 0);
			error = 2;
		}
		else if (invalid_path(path))
			error = check_error(error, path);
		i++;
		free(path);
	}
	return (error);
}
