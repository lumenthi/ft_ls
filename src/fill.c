/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:13:21 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/13 11:46:55 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file		*file_init(t_file *file)
{
	file->perm = 0;
	file->links = 0;
	file->owner = NULL;
	file->group = NULL;
	file->size = 0;
	file->name = NULL;
	file->blocks = 0;
	file->link_name = NULL;
	file->next = NULL;
	return (file);
}

void		struct_fill(t_file **files, t_file **h, t_dir *content, char *path)
{
	if ((*files) == NULL)
	{
		(*files) = malloc(sizeof(t_file));
		if (!(*h))
			(*h) = (*files);
		(*files) = file_init((*files));
	}
	fill_all((*files), content, path);
	(*files)->next = malloc(sizeof(t_file));
	(*files) = (*files)->next;
	(*files) = file_init((*files));
}

t_file		*file_fill_a(char *path)
{
	DIR		*dir;
	t_dir	*content;
	t_file	*files;
	t_file	*head;

	files = NULL;
	head = NULL;
	if (!(dir = opendir(path)))
	{
		print_error(path, errno, 0);
		return (NULL);
	}
	while ((content = readdir(dir)))
		struct_fill(&files, &head, content, path);
	(closedir(dir) == -1) ? print_error(path, errno, 0) : 1;
	return (head);
}

t_file		*file_fill_single(char *path, char *single)
{
	DIR		*dir;
	t_dir	*content;
	t_file	*files;

	files = NULL;
	if (!(dir = opendir(path)))
		return (NULL);
	while ((content = readdir(dir)))
	{
		if (ft_strcmp(content->d_name, single) == 0)
		{
			files = malloc(sizeof(t_file));
			files = file_init(files);
			fill_all(files, content, path);
			files->next = NULL;
			break ;
		}
	}
	if (closedir(dir) == -1)
		print_error(path, errno, 0);
	if (!files || !files->name)
		return (NULL);
	return (files);
}

t_file		*file_fill(char *path)
{
	DIR		*dir;
	t_dir	*content;
	t_file	*files;
	t_file	*head;

	files = NULL;
	head = NULL;
	if (!(dir = opendir(path)))
	{
		print_error(path, errno, 0);
		return (NULL);
	}
	while ((content = readdir(dir)))
	{
		if (content->d_name[0] != '.')
			struct_fill(&files, &head, content, path);
	}
	(closedir(dir) == -1) ? print_error(path, errno, 0) : 1;
	return (head);
}
