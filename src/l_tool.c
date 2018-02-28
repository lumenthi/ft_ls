/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_tool.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 11:32:46 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/20 19:24:13 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char				*time_conv(char *str)
{
	char	*time;

	time = malloc(13);
	time = ft_strncpy(time, str + 4, 12);
	time[12] = '\0';
	return (time);
}

int					max_userlen(t_file *file)
{
	int max_length;

	max_length = 0;
	if (!file)
		return (0);
	while (file->next)
	{
		if ((int)ft_strlen(file->owner) > max_length)
			max_length = ft_strlen(file->owner);
		file = file->next;
	}
	return (max_length);
}

unsigned long long	block_count(t_file *files)
{
	unsigned long long total;

	if (!files)
		return (0);
	total = 0;
	while (files->next)
	{
		total = total + files->blocks;
		files = files->next;
	}
	return (total);
}

int					max_size(t_file *file)
{
	int max_length;

	max_length = 0;
	if (!file)
		return (0);
	while (file->next)
	{
		if ((int)ft_strlen(file->size) > max_length)
			max_length = ft_strlen(file->size);
		file = file->next;
	}
	return (max_length);
}

int					max_link(t_file *file)
{
	int max_length;

	max_length = 0;
	if (!file)
		return (0);
	while (file->next)
	{
		if ((int)file->links > max_length)
			max_length = file->links;
		file = file->next;
	}
	return (max_length);
}
