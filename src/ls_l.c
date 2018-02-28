/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_l.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:13:21 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/22 13:59:45 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		perm_print(mode_t mode)
{
	first_perm(mode);
	(mode & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(mode & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	if (mode & S_ISUID)
		ft_putchar((mode & S_IXUSR) ? 's' : 'S');
	else
		ft_putchar((mode & S_IXUSR) ? 'x' : '-');
	(mode & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(mode & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	if (mode & S_ISGID)
		ft_putchar((mode & S_IXGRP) ? 's' : 'S');
	else
		ft_putchar((mode & S_IXGRP) ? 'x' : '-');
	(mode & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(mode & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	if (mode & S_ISVTX)
		ft_putchar((mode & S_IXOTH) ? 't' : 'T');
	else
		ft_putchar((mode & S_IXOTH) ? 'x' : '-');
}

void		print_spaces(int max, int nb)
{
	int		difference;

	difference = max - nb;
	if (difference < 0)
		return ;
	while (difference)
	{
		ft_putchar(' ');
		difference--;
	}
}

static void	l_print_1(t_file *files, int max_l, int max_g, int max_o)
{
	perm_print(files->perm);
	ft_putstr("  ");
	print_spaces(ft_intlen(max_l), ft_intlen(files->links));
	ft_putnbr(files->links);
	ft_putchar(' ');
	files->owner ? ft_putstr(files->owner) : ft_putstr("");
	ft_putstr("  ");
	print_spaces(max_o, ft_strlen(files->owner));
	files->group ? ft_putstr(files->group) : ft_putstr("");
	ft_putstr("  ");
	print_spaces(max_g, ft_strlen(files->group));
}

static void	l_print_2(t_file *files, int max_s)
{
	print_spaces(max_s, ft_strlen(files->size));
	files->size ? ft_putstr(files->size) : ft_putstr("0");
	ft_putchar(' ');
	print_date(files);
	ft_putchar(' ');
	ft_putstr(files->name);
	if (files->link_name)
		ft_putstr(files->link_name);
	ft_putchar('\n');
}

void		l_print(t_file *files, int s)
{
	unsigned long long	blocks;
	int					max_l;
	int					max_s;
	int					max_o;
	int					max_g;

	blocks = block_count(files);
	max_g = max_grouplen(files);
	max_l = max_link(files);
	max_s = max_size(files);
	max_o = max_userlen(files);
	l_print_total(files, s, blocks);
	while (files && files->next != NULL)
	{
		if (files && files->owner)
		{
			l_print_1(files, max_l, max_g, max_o);
			l_print_2(files, max_s);
		}
		files = files->next;
	}
}
