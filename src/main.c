/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 16:21:54 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/26 10:32:39 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	get_args(char *str, char **args)
{
	while (*str)
	{
		if (*str == 'l')
			*(*args + 0) = '1';
		if (*str == 'R')
			*(*args + 1) = '1';
		if (*str == 'a')
			*(*args + 2) = '1';
		if (*str == 'r')
			*(*args + 3) = '1';
		if (*str == 't')
			*(*args + 4) = '1';
		str++;
	}
}

void	make_path2(char **argv, int i, char **path)
{
	if (argv[i][0] != '/')
		*path = make_path(".", argv[i]);
	else
		*path = ft_strdup(argv[i]);
}

char	*all_args(int argc, char **argv)
{
	char	*args;
	int		i;
	int		j;
	int		c;

	args = ft_strdup("00000");
	c = 1;
	i = 1;
	j = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--") == 0 || argv[i][0] != '-')
			break ;
		while (argv[i][c])
		{
			if ((j = ft_strchr_index("alRrtdG1Ss", argv[i][c])) == -1)
				print_error(NULL, USAGE, argv[i][c]);
			c++;
		}
		c = 1;
		get_args(argv[i], &args);
		i++;
	}
	return (args);
}

int		main(int argc, char **argv)
{
	char	*args;
	int		i;
	t_file	*files;

	files = NULL;
	args = all_args(argc, argv);
	i = pass_args(argc, argv, 1);
	argv = sort_f(argc, argv, args, i);
	if (argc == 1 || i == argc)
	{
		apply_args(args, &files, "./");
		file_del(&files);
	}
	else
		ft_ls(argc, argv, args, i);
	free(args);
	while (1);
	return (0);
}
