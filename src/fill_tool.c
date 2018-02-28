/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 12:12:15 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/26 11:07:40 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file		*lst_name_fill(t_file *file, t_dir *content)
{
	file->name = ft_strdup(content->d_name);
	return (file);
}

t_file		*lst_go_fill(t_file *file, char *str, char *path, t_stat *stats)
{
	struct group	*grp;
	struct passwd	*user;
	char			*new_path;

	grp = NULL;
	user = NULL;
	new_path = make_path(path, str);
	if (!ferror(file, &new_path, &stats))
		return (NULL);
	free(new_path);
	if (!stats)
		return (file);
	if ((grp = getgrgid(stats->st_gid)) && grp->gr_name)
		file->group = ft_strdup(grp->gr_name);
	else
		file->group = ft_itoa(stats->st_gid);
	user = getpwuid(stats->st_uid);
	if ((user = getpwuid(stats->st_uid)) && user->pw_name)
		file->owner = ft_strdup(user->pw_name);
	else
		file->owner = ft_itoa(stats->st_uid);
	return (file);
}

t_file		*lst_all_fill(t_file *file, char *str, char *path, t_stat *stats)
{
	char *new_path;

	new_path = make_path(path, str);
	file->link_name ? lstat(new_path, stats) : stat(new_path, stats);
	free(new_path);
	if (!stats)
		return (file);
	file->perm = stats->st_mode;
	file->blocks = (unsigned long long)stats->st_blocks;
	file->links = (unsigned long long)stats->st_nlink;
	file->time = stats->st_mtimespec;
	if (stats->st_rdev != 0)
		file->size = sp_si(major(stats->st_rdev), minor(stats->st_rdev));
	else
		file->size = ft_itoa(stats->st_size);
	return (file);
}

t_file		*lst_linkname_fill(t_file *file, char *str, char *path)
{
	char	*buf;
	char	*link;
	int		ret;
	char	*new_path;
	char	*new;

	new = NULL;
	buf = malloc(1000);
	link = " -> ";
	ret = 0;
	file->link_name = NULL;
	new_path = make_path(path, str);
	if ((ret = readlink(new_path, buf, 1000)) > 0)
	{
		buf[ret] = '\0';
		new = ft_strjoin(link, buf);
		file->link_name = ft_strdup(new);
	}
	free(new);
	free(buf);
	free(new_path);
	return (file);
}

t_file		*fill_all(t_file *files, t_dir *content, char *path)
{
	t_stat *stats;

	stats = malloc(sizeof(t_stat));
	files = lst_name_fill(files, content);
	files = lst_linkname_fill(files, files->name, path);
	if (!(files = lst_go_fill(files, files->name, path, stats)))
	{
		free(stats);
		return (files);
	}
	files = lst_all_fill(files, files->name, path, stats);
	free(stats);
	return (files);
}
