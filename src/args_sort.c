/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 11:04:10 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/21 18:16:43 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				get_valid_path(int argc, char **argv, int init)
{
	int		count;
	char	*path_c;

	count = 0;
	path_c = NULL;
	while (argc >= init)
	{
		while (argv[argc] == NULL)
			argc--;
		path_c = get_path(argv[argc]);
		if (invalid_path(path_c) == 20 ||
			!invalid_path(path_c) || is_sym(&path_c))
			count++;
		free(path_c);
		argc--;
	}
	return (count);
}

int				valid_args_i(char **argv, int i)
{
	char *path_i;

	path_i = NULL;
	while (argv[i])
	{
		while (argv[i] == NULL)
			i++;
		path_i = get_path(argv[i]);
		if (invalid_path(path_i) == 20 || !invalid_path(path_i) ||
			is_sym(&path_i))
		{
			free(path_i);
			break ;
		}
		free(path_i);
		i++;
	}
	return (i);
}

int				valid_args_c(char **argv, int argc, int init)
{
	char *path_c;

	path_c = NULL;
	while (argc > init)
	{
		while (argv[argc] == NULL)
			argc--;
		path_c = get_path(argv[argc]);
		if (invalid_path(path_c) == 20 || !invalid_path(path_c) ||
			is_sym(&path_c))
		{
			free(path_c);
			break ;
		}
		free(path_c);
		argc--;
	}
	return (argc);
}

struct timespec	get_time(char *arg)
{
	t_stat			*stats;
	struct timespec	time;
	char			*path;

	stats = malloc(sizeof(t_stat));
	path = get_path(arg);
	is_sym(&path) ? lstat(path, stats) : stat(path, stats);
	time = stats->st_mtimespec;
	free(stats);
	if (invalid_path(path) != 20 && invalid_path(path))
	{
		time.tv_sec = 0;
		time.tv_nsec = 0;
	}
	free(path);
	return (time);
}
