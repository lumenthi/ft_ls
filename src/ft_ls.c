/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 16:21:54 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/22 14:30:04 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	apply_args(char *args, t_file **files, char *path)
{
	if (args[2] == '1')
		*files = file_fill_a(path);
	if (args[2] == '0')
		*files = file_fill(path);
	if ((!(*files)) || (*files && !(*files)->owner && (args[0] == '1' ||
		args[4] == '1' || args[3] == '1')))
		return ;
	*files = sort(*files);
	if (args[4] == '1')
		*files = sort_t(*files);
	if (args[3] == '1')
		*files = sort_r(*files);
	if (args[0] == '1')
		l_print(*files, 0);
	if (args[0] == '0')
		ls_print(*files);
	if (args[1] == '1')
	{
		args[1] = '0';
		r_print(args, *files, path);
		args[1] = '1';
	}
}

int		pass_args(int argc, char **argv, int i)
{
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--") == 0)
			return (i + 1);
		if (ft_strcmp(argv[i], "-") == 0 || argv[i][0] != '-')
			break ;
		i++;
	}
	return (i);
}

void	path_print(char *path, int argc, int check)
{
	if (argc - check > 1)
	{
		if (path[0] == '.' && path[1] == '/')
			ft_putstr(path + 2);
		else
			ft_putstr(path);
		ft_putendl(":");
	}
}

void	space_errors(int i, int error, int args_er, int check)
{
	if (i != 1 && !error && !args_er && i != check)
		ft_putchar('\n');
	if (error && args_er == 1)
		ft_putchar('\n');
	if (args_er == 99 || (args_er == 1 && error == 0))
		ft_putchar('\n');
}

void	ft_ls(int argc, char **argv, char *args, int i)
{
	t_file	*files;
	char	*path;
	int		error;
	int		args_er;
	int		check;

	ft_ls_init(&files, &check, i);
	error = print_all_error(argc, argv, i);
	args_er = print_args(argc, argv, args, i);
	while (i < argc)
	{
		if (path_maker(argv, &i, &path, argc))
			break ;
		if (!invalid_path(path) || invalid_path(path) == 13)
		{
			space_errors(i, error, args_er, check);
			path_print(path, argc, check);
			apply_args(args, &files, path);
			error_init(&error, &args_er);
			file_del(&files);
		}
		free(path);
		i++;
	}
}
