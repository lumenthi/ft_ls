/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_tool2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 14:41:05 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/22 14:00:40 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_date_tool(t_file *files, char **ret)
{
	char	*month;
	char	*year;
	int		spaces;

	year = ctime(&files->time.tv_sec);
	if (!year)
		return ;
	month = time_conv(year);
	month[7] = '\0';
	year = year + 20;
	year[ft_strlen(year) - 1] = '\0';
	spaces = 5 - ft_strlen(year);
	spaces <= 0 ? spaces = 1 : spaces;
	while (*year == ' ')
		year++;
	while (spaces--)
		year = ft_strjoin(" ", year);
	*ret = ft_strjoin(month, year);
	free(month);
	year ? free(year) : 0;
	ft_putstr(*ret);
	free(*ret);
}

void	print_date(t_file *files)
{
	char	*ret;

	ret = NULL;
	if (files->time.tv_sec - time(NULL) > 15778800 ||
		files->time.tv_sec - time(NULL) < -15778800)
		print_date_tool(files, &ret);
	else
	{
		ret = time_conv(ctime(&files->time.tv_sec));
		ft_putstr(ret);
		free(ret);
	}
}

int		max_grouplen(t_file *file)
{
	int max_length;

	max_length = 0;
	if (!file)
		return (0);
	while (file->next)
	{
		if ((int)ft_strlen(file->group) > max_length)
			max_length = ft_strlen(file->group);
		file = file->next;
	}
	return (max_length);
}

void	first_perm(mode_t mode)
{
	(S_ISFIFO(mode)) ? ft_putchar('p') : 1;
	(S_ISCHR(mode)) ? ft_putchar('c') : 1;
	(S_ISDIR(mode)) ? ft_putchar('d') : 1;
	(S_ISBLK(mode)) ? ft_putchar('b') : 1;
	(S_ISLNK(mode)) ? ft_putchar('l') : 1;
	(S_ISREG(mode)) ? ft_putchar('-') : 1;
	(S_ISSOCK(mode)) ? ft_putchar('s') : 1;
}

void	l_print_total(t_file *files, int s, long long blocks)
{
	if (files && files->next && s == 0)
	{
		ft_putstr("total ");
		ft_putnbr(blocks);
		ft_putchar('\n');
	}
}
