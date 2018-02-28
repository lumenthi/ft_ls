/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:13:20 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/21 17:13:42 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	**a_sort(char **argv, int init)
{
	int	i;
	int	j;

	i = init;
	j = init;
	while (argv[j])
	{
		while (argv[i])
		{
			if (ft_strcmp(argv[j], argv[i]) < 0)
				ft_strswap(&argv[j], &argv[i]);
			i++;
		}
		i = init;
		j++;
	}
	return (argv);
}

char	**a_sort_t(char **argv, int init)
{
	int				i;
	int				j;
	struct timespec	ti;
	struct timespec	tj;

	j = init;
	while (argv[j])
	{
		i = init;
		while (argv[i])
		{
			ti = get_time(argv[i]);
			tj = get_time(argv[j]);
			if (tj.tv_sec == ti.tv_sec && tj.tv_nsec > ti.tv_nsec
				&& ti.tv_sec != 0 && tj.tv_sec != 0)
				ft_strswap(&argv[j], &argv[i]);
			else if (tj.tv_sec > ti.tv_sec && ti.tv_sec != 0 && tj.tv_sec != 0)
				ft_strswap(&argv[j], &argv[i]);
			i++;
		}
		j++;
	}
	return (argv);
}

char	**a_sort_r(int argc, char **argv, int init)
{
	int	i;
	int	valid_args;

	valid_args = get_valid_path(argc, argv, init) / 2;
	i = init;
	while (valid_args)
	{
		i = valid_args_i(argv, i);
		argc = valid_args_c(argv, argc, init);
		ft_strswap(&argv[i], &argv[argc]);
		argc--;
		i++;
		valid_args--;
	}
	return (argv);
}

char	**sort_f(int argc, char **argv, char *args, int init)
{
	argv = a_sort(argv, init);
	if (args[4] == '1')
		argv = a_sort_t(argv, init);
	if (args[3] == '1')
		argv = a_sort_r(argc, argv, init);
	return (argv);
}
