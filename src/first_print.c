/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 13:22:06 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/26 10:48:02 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	lst_cpy(t_file *dest, t_file *src)
{
	dest->perm = src->perm;
	dest->links = src->links;
	dest->owner = ft_strdup(src->owner);
	dest->group = ft_strdup(src->group);
	dest->size = src->size;
	dest->time = src->time;
	dest->name = ft_strdup(src->name);
	dest->blocks = src->blocks;
	if (src->link_name)
		dest->link_name = ft_strdup(src->link_name);
	else
		dest->link_name = NULL;
}

void	single_fill(char *path, t_file **single_file)
{
	char *pf;
	char *tmp;
	char *single;

	pf = ft_strdup(path);
	single = "";
	single = ft_strrchr(pf, '/') + 1;
	tmp = ft_strdup(single);
	*single = '\0';
	*(single_file) = NULL;
	*(single_file) = file_fill_single(pf, tmp);
	free(pf);
	free(tmp);
}

void	do_things(char *path, t_file **single_file, t_file **head, t_file **h)
{
	single_fill(path, single_file);
	if (!(*head) && (*single_file))
	{
		(*head) = malloc(sizeof(t_file));
		(*h) = (*head);
		(*h)->name = NULL;
	}
	if ((*single_file) && (*single_file)->name != NULL)
	{
		lst_cpy((*head), (*single_file));
		free((*head)->name);
		(*head)->next = malloc(sizeof(t_file));
		if (path[0] != '/')
			(*head)->name = ft_strdup(path + 2);
		else
			(*head)->name = ft_strdup(path);
		(*head) = (*head)->next;
		free((*single_file)->name);
		free((*single_file)->link_name);
		free((*single_file)->group);
		free((*single_file)->owner);
		free((*single_file));
	}
}

void	dt2(t_file **head, t_file **head2, char *args, int *error)
{
	if (*head && (*head2)->name)
	{
		(*head)->next = NULL;
		args[0] == '1' ? l_print(*head2, 1) : ls_print(*head2);
		*error != 99 ? *error = 1 : 99;
		file_del(head2);
	}
}

int		print_args(int argc, char **argv, char *args, int i)
{
	char	*path;
	int		error;
	t_file	*single_file;
	t_file	*head;
	t_file	*head2;

	head = NULL;
	while (i < argc)
	{
		make_path2(argv, i, &path);
		if (args[0] == '1' && is_sym(&path))
		{
			do_things(path, &single_file, &head, &head2);
			argv[i] = NULL;
			error = 99;
		}
		else if ((error = invalid_path(path)) == 20 || error == 2)
			do_things(path, &single_file, &head, &head2);
		i++;
		free(path);
	}
	error != 99 ? error = 0 : 99;
	dt2(&head, &head2, args, &error);
	return (error);
}
