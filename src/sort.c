/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 16:50:12 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/13 11:27:23 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	cpy_all(t_file *dest, t_file *src, t_file *tmp)
{
	tmp->perm = dest->perm;
	tmp->links = dest->links;
	tmp->owner = dest->owner;
	tmp->group = dest->group;
	tmp->size = dest->size;
	tmp->time = dest->time;
	tmp->name = dest->name;
	tmp->link_name = dest->link_name;
	dest->perm = src->perm;
	dest->links = src->links;
	dest->owner = src->owner;
	dest->group = src->group;
	dest->size = src->size;
	dest->time = src->time;
	dest->name = src->name;
	dest->link_name = src->link_name;
	src->perm = tmp->perm;
	src->links = tmp->links;
	src->owner = tmp->owner;
	src->group = tmp->group;
	src->size = tmp->size;
	src->time = tmp->time;
	src->name = tmp->name;
	src->link_name = tmp->link_name;
}

void	cpy(t_file *dest, t_file *src)
{
	t_file *tmp;

	tmp = malloc(sizeof(t_file));
	cpy_all(dest, src, tmp);
	free(tmp);
}

t_file	*sort(t_file *file)
{
	t_file *head;
	t_file *tmp;

	if (!file)
		return (NULL);
	head = file;
	tmp = file;
	while (tmp->next)
	{
		while (file->next)
		{
			if (ft_strcmp(tmp->name, (file->name)) < 0)
				cpy(tmp, file);
			file = file->next;
		}
		file = head;
		tmp = tmp->next;
	}
	return (head);
}

t_file	*sort_t(t_file *file)
{
	t_file *head;
	t_file *tmp;

	head = file;
	tmp = file;
	while (tmp && tmp->next)
	{
		while (file->next)
		{
			if (tmp->time.tv_sec - file->time.tv_sec > 0)
				cpy(tmp, file);
			else if (tmp->time.tv_sec == file->time.tv_sec
			&& tmp->time.tv_nsec - file->time.tv_nsec > 0)
				cpy(tmp, file);
			else if (tmp->time.tv_sec == file->time.tv_sec
			&& tmp->time.tv_nsec == file->time.tv_nsec &&
			ft_strcmp(tmp->name, file->name) < 0)
				cpy(tmp, file);
			file = file->next;
		}
		file = head;
		tmp = tmp->next;
	}
	return (head);
}

t_file	*sort_r(t_file *file)
{
	t_file	*head;
	t_file	*tmp;
	int		c;
	int		lim;
	int		m;

	c = 1;
	lim = lst_len(file);
	head = file;
	tmp = file;
	m = lim / 2;
	while (lim > m)
	{
		while (c < lim)
		{
			file = file->next;
			c++;
		}
		c = 1;
		cpy(tmp, file);
		lim--;
		tmp = tmp->next;
		file = head;
	}
	return (head);
}
